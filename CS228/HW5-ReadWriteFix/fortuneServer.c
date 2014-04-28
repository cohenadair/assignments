/* A simple server in the internet domain using TCP
 * The port number is passed as an argument 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include "NMUSocket.h"
#include "fortune.h"

#include <signal.h>

void sigchld_handler(int s)
{
	while(waitpid(-1, NULL, WNOHANG) > 0);
}

void handleFortuneServerProtocol(nmu_socket_t serviceSocket);

void handleOptions( int argc, char *argv[], int *portnoPtr )
{
     if (argc != 2){ 
    	fprintf(stderr, "usage: %s <port number>\n", argv[0]);
    	exit(-1);
	}
	*portnoPtr = atoi(argv[1]);
}

int main(int argc, char *argv[])
{
	int port;
	bool notDone = true;
	nmu_socket_t serverSocket;
	struct sigaction sigact;

	handleOptions( argc, argv, &port );
	socketFactory.initialize();
	sigact.sa_handler = sigchld_handler;
	sigemptyset(&sigact.sa_mask);
	sigact.sa_flags = SA_RESTART;
	if( sigaction(SIGCHLD, &sigact, NULL) == -1){
		fprintf(stderr, "Could not set SIGCHLD handler.\n");
		exit(-1);
	}

	serverSocket = socketFactory.serveTCPForHostnameAndPort( "localhost", port );
	while( notDone ) {
		pid_t childPid;

		nmu_socket_t serviceSocket;
		serviceSocket = serverSocket->accept(serverSocket);
		childPid = fork();
		if(childPid < 0){ // fork() failed
			fprintf( stderr, "Could not fork protocol handler.\n" );
			serviceSocket->close(serviceSocket);
		}
		if(childPid){ // The parent doesn't need the service socket.
			serviceSocket->close(serviceSocket);
		}
		else { // The child doesn't need the server socket.
			serverSocket->close(serverSocket);
			handleFortuneServerProtocol(serviceSocket);
			exit(0); //The child is done and may be excused.
		}
	}
	serverSocket->close(serverSocket);
	return 0; 
}

static char * fortunes[] = {
	"A man in a red flannel suit will visit you in December.\n",
	"1999 is sooooo last millenium.\n",
	"Answer hazy, ask again later.\n",
};

int handleFortuneRequest(nmu_socket_t serviceSocket);
int handleFortuneQuit(nmu_socket_t serviceSocket);

static int fortuneIndex = 0;
static int state;

void handleFortuneServerProtocol(nmu_socket_t serviceSocket)
{
	uint8_t pduId;
	
	state = RUNNING;
	while( state != DONE ){
		serviceSocket->read(serviceSocket, &pduId, sizeof(uint8_t));
		switch( pduId ){
		case FORTUNE_REQUEST:
			state = handleFortuneRequest(serviceSocket);
			break;
		case FORTUNE_QUIT:
			state = handleFortuneQuit(serviceSocket);
			break;
		case 0:
			break;
		default:
			serviceSocket->error(serviceSocket, "ERROR, protocol error" );
		}
	}
}

int handleFortuneRequest(nmu_socket_t serviceSocket)
{
	uint8_t	fortuneReply = FORTUNE_REPLY; 
	uint8_t count = (uint8_t)strlen(fortunes[fortuneIndex % 3]);

	serviceSocket->write(serviceSocket, &fortuneReply, sizeof(uint8_t));
	count = strlen(fortunes[fortuneIndex % 3]);
	serviceSocket->write(serviceSocket, &count, sizeof(uint8_t));
	serviceSocket->write(serviceSocket, fortunes[fortuneIndex++ % 3], count);
	return RUNNING;
}

int handleFortuneQuit(nmu_socket_t serviceSocket)
{
	serviceSocket->close(serviceSocket);
	return DONE;
}
