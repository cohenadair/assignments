#include "NMUSocket.h"

bool UnixinitializeNetwork(void);
nmu_socket_t UnixAllocSocket(void);
nmu_socket_t UnixServeTCPSocket(char *hostname, short port);
nmu_socket_t UnixConnectTCPSocket(char *hostname, char *port);
void Unixlisten(nmu_socket_t pSocket);
nmu_socket_t Unixaccept(nmu_socket_t pSocket);
int Unixread(nmu_socket_t pSocket, void *buffer, int bufferSize);
int Unixwrite(nmu_socket_t pSocket, void *buffer, int bufferSize);
void Unixclose(nmu_socket_t pSocket);
void Unixerror(nmu_socket_t pSocket, char *msg);

NMUSocketFactory socketFactory = {
	UnixServeTCPSocket,
	UnixConnectTCPSocket,
	UnixinitializeNetwork,
	UnixAllocSocket,
	false
};
	
bool UnixinitializeNetwork(void)
{
	socketFactory.initialized = true;
	return true;
}

nmu_socket_t UnixAllocSocket(void)
{
	nmu_socket_t pSocket = (nmu_socket_t)calloc(1, sizeof(NMUSocket));
	pSocket->accept = Unixaccept;
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
	int result = 0, tmp = 0;
	memset(buffer, 0, bufferSize);

	while (result < bufferSize) {
		while ((tmp = read(pSocket->sockfd, buffer + result, bufferSize - result)) < 0) {
			if (!(errno == EINTR))
				pSocket->error(pSocket, "Error on read");
		}

		result += tmp;
	}

	return result;
}

int Unixwrite(nmu_socket_t pSocket, void *buffer, int count)
{
	int result = 0, tmp = 0;

	while (result < count) {
		while ((tmp = write(pSocket->sockfd, buffer + result, count - result)) < 0) {
			if (!(errno == EINTR))
				pSocket->error(pSocket, "Error on write");
		}

		result += tmp;
	}

	return result;
}

void Unixerror(nmu_socket_t pSocket, char *msg)
{
    perror(msg);
    exit(1);
}

