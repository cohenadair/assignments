#include "NMUSocket.h"
#include <errno.h>

#ifdef THREADED_SERVER
	#include <pthread.h>
#else
	#include <signal.h>
	
	void sigchld_handler(int s)
	{
		while(waitpid(-1, NULL, WNOHANG) > 0);
	}
#endif

bool UnixinitializeNetwork(void);
nmu_socket_t UnixAllocSocket(void);
nmu_socket_t UnixServeTCPSocket(char *hostname, short port);
nmu_socket_t UnixConnectTCPSocket(char *hostname, char *port);
void Unixlisten(nmu_socket_t pSocket);
nmu_socket_t Unixaccept(nmu_socket_t pSocket);
void UnixAcceptAndServe(nmu_socket_t serveSocket, pFunPVS protocolHandler);
int Unixread(nmu_socket_t pSocket, void *buffer, int bufferSize);
int Unixwrite(nmu_socket_t pSocket, void *buffer, int bufferSize);
void Unixclose(nmu_socket_t pSocket);
void Unixerror(nmu_socket_t pSocket, char *msg);
void pthreadError(nmu_socket_t pSocket, char *msg);

NMUSocketFactory socketFactory = {
	UnixServeTCPSocket,
	UnixConnectTCPSocket,
	UnixinitializeNetwork,
	UnixAllocSocket,
	false
};
	
bool UnixinitializeNetwork(void)
{
	if( socketFactory.initialized == true )
		return true;
	socketFactory.initialized = true;
	
#ifndef THREADED_SERVER
	struct sigaction sigact;
	sigact.sa_handler = sigchld_handler;
	sigemptyset(&sigact.sa_mask);
	sigact.sa_flags = SA_RESTART;
	if( sigaction(SIGCHLD, &sigact, NULL) == -1){
		fprintf(stderr, "Could not set SIGCHLD handler.\n");
		exit(-1);
	}
#endif
	
	return true;
}

nmu_socket_t UnixAllocSocket(void)
{
	nmu_socket_t pSocket = (nmu_socket_t)calloc(1, sizeof(NMUSocket));
	pSocket->accept = Unixaccept;
	pSocket->acceptAndServe = UnixAcceptAndServe;
	pSocket->read = Unixread;
	pSocket->write = Unixwrite;
	pSocket->close = Unixclose;
	pSocket->error = Unixerror;
	return pSocket;
}

nmu_socket_t UnixServeTCPSocket(char *hostname, short port)
{
	// Create a server socket.
	nmu_socket_t pSocket = socketFactory.new();
	if(pSocket == NULL)
		return NULL;
	pSocket->sockfd = socket(AF_INET, SOCK_STREAM, 0);

	// Initialize and bind the server socket.
	memset((char *) &pSocket->sockAddr, 0, sizeof(SocketAddress));
	pSocket->sockAddr.sin_family = AF_INET;
	pSocket->sockAddr.sin_addr.s_addr = INADDR_ANY;
	pSocket->sockAddr.sin_port = htons(port);

	// Bind to service port.
	if( bind(pSocket->sockfd, (struct sockaddr *) &pSocket->sockAddr, sizeof(SocketAddress)) < 0) 
		pSocket->error(pSocket, "ERROR on binding");

	// Listen for connection requests.
	if(listen(pSocket->sockfd,5) < 0)
		pSocket->error( pSocket, "ERROR on listen" );;

	return pSocket;
}

nmu_socket_t UnixConnectTCPSocket(char *hostname, char *port)
{
	nmu_socket_t pSocket = socketFactory.new();
	struct addrinfo *result = NULL;
	struct addrinfo *next = NULL;
	struct addrinfo hints;
	int returnValue;

	// Use getaddrinfo to find all possible IPV4 TCP sockets.
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	returnValue = getaddrinfo(hostname, port, &hints, &result);
	if(returnValue != 0){
		fprintf(stderr, "getaddrinfo() failed\n");
		exit(-1);
	}
	// Run through available addresses, till a successful connection.
	for(next = result; next != NULL; next = next->ai_next){
		// Open socket on this address.
		pSocket->sockfd = socket(next->ai_family, next->ai_socktype, next->ai_protocol);
		if( pSocket->sockfd == -1 )
			continue;
		// Connect to server..
		if(connect(pSocket->sockfd, next->ai_addr, next->ai_addrlen) == -1){
			close(pSocket->sockfd);
			pSocket->sockfd = -1;
			continue;
		}
		// if we get here, successful connection
		break;
	}
	freeaddrinfo(result);
	if( pSocket->sockfd == -1 ){
		fprintf(stderr, "Error: Unable to connect to server.\n");
		exit(-1);
	}
	return pSocket;
}

nmu_socket_t Unixaccept(nmu_socket_t pSocket)
{
	socklen_t sockAddrLength = sizeof(SocketAddress);
	nmu_socket_t pClientSocket = socketFactory.new();
	int newsockfd = 
		accept(pSocket->sockfd, (struct sockaddr *)&(pClientSocket->sockAddr), &sockAddrLength);
	if (newsockfd < 0){
		free(pClientSocket); 
		pSocket->error(pSocket, "ERROR on accept");
	}
	pClientSocket->sockfd = newsockfd;
	return pClientSocket;
}

void UnixAcceptAndServe(nmu_socket_t serveSocket, pFunPVS protocolHandler)
{
	nmu_socket_t serviceSocket;
	serviceSocket = serveSocket->accept(serveSocket);
	
#ifdef THREADED_SERVER
	int result = 0;
	pthread_t pThreadId;
	serviceSocket->error = pthreadError;
	result = pthread_create(&pThreadId, NULL, (pFunThread)protocolHandler, serviceSocket);
	if (result != 0) {
		fprintf(stderr, "Failed to thread protocol handler.\n");
		serviceSocket->close(serviceSocket);
	}
#else
	pid_t childPid;
	childPid = fork();
	
	if(childPid < 0){ // fork() or pthread_create() failed
		fprintf( stderr, "Could not fork protocol handler.\n" );
		serviceSocket->close(serviceSocket);
	}
	if(childPid){ // The parent doesn't need the service socket.
		serviceSocket->close(serviceSocket);
	}
	else { // The child doesn't need the server socket.
		serveSocket->close(serveSocket);
		protocolHandler(serviceSocket);
		exit(0); //The child is done and may be excused.
	}
#endif
}

bool Unixconnect(nmu_socket_t pSocket)
{
    return connect(
		pSocket->sockfd,
		(struct sockaddr *)&pSocket->sockAddr,
		sizeof(SocketAddress)) == 0;
}

void Unixclose(nmu_socket_t pSocket)
{
	close(pSocket->sockfd);
	free(pSocket);
}

int Unixread(nmu_socket_t pSocket, void *buffer, int bufferSize)
{
	int totalBytesRead = 0;
	int	bytesRead;
	uint8_t *buff = buffer;

	memset(buffer, 0, bufferSize);
	while( totalBytesRead < bufferSize){
		do{
			bytesRead = read(	
				pSocket->sockfd, 
				buff+totalBytesRead, 
				bufferSize - totalBytesRead);
			if(bytesRead < 0 && errno != EINTR)
				pSocket->error(pSocket, "NMUSocket:read failed\n");
		}
		while(bytesRead < 0);
		totalBytesRead += bytesRead;
	}
	return bytesRead;
}

int Unixwrite(nmu_socket_t pSocket, void *buffer, int count)
{
	int totalBytesWritten = 0;
	int	bytesWritten;
	uint8_t *buff = buffer;

	while( totalBytesWritten < count){
		do{
			bytesWritten = write(	
				pSocket->sockfd, 
				buff + totalBytesWritten, 
				count - totalBytesWritten);
			if(bytesWritten < 0 && errno != EINTR)
				pSocket->error(pSocket, "NMUSocket:write failed\n");
		}
		while(bytesWritten < 0);
		totalBytesWritten += bytesWritten;
	}
	return bytesWritten;
}

void Unixerror(nmu_socket_t pSocket, char *msg)
{
    perror(msg);
    exit(1);
}

void pthreadError(nmu_socket_t pSocket, char *msg) {
	perror(msg);
	pthread_exit(NULL);
}

