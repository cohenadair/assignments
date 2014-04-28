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
#include <pthread.h>
#include "NMUSocket.h"
#include "fortune.h"

void * handleFortuneServerProtocol(nmu_socket_t serviceSocket);

void handleOptions( int argc, char *argv[], int *portnoPtr )
{
     if (argc < 2){ 
    	fprintf(stderr, "%s\n", "ERROR, no port provided");
    	exit(-1);
	}
	*portnoPtr = atoi(argv[1]);
}

pthread_mutex_t fortuneMutex;

int main(int argc, char *argv[])
{
	int port;
	int notDone = 1;
	nmu_socket_t serverSocket;
	pthread_mutex_init(&fortuneMutex, NULL);
	
	socketFactory.initialize();
	handleOptions( argc, argv, &port );
	serverSocket = socketFactory.serveTCPForHostnameAndPort( "localhost", port);
	while( notDone ) 
		serverSocket->acceptAndServe(serverSocket, handleFortuneServerProtocol);
	serverSocket->close(serverSocket);
	pthread_mutex_destroy(&fortuneMutex);
	return 0; 
}

int handleFortuneRequest(nmu_socket_t serviceSocket);
int handleFortuneQuit(nmu_socket_t serviceSocket);
int handleFortuneError(nmu_socket_t serviceSocket);

static int fortuneIndex = 0;

void * handleFortuneServerProtocol(nmu_socket_t serviceSocket)
{
	// Protocol State Machine
	// 			FORTUNE_REQUEST	FORTUNE_REPLY	FORTUNE_QUIT
	// RUNNING	handleRequest	error			handleReply
	// DONE		error			error			error
	//

	pFunIS protocol[NUM_STATES][NUM_PDUS] = {
		{ handleFortuneRequest, handleFortuneError, handleFortuneQuit },
		{ handleFortuneError,   handleFortuneError, handleFortuneError },
	};
	
	uint8_t pduId;
	int state = 0;	
	
	state = RUNNING;
	while( state != DONE ){
		serviceSocket->read(serviceSocket, &pduId, sizeof(uint8_t));
		if( !(FORTUNE_REQUEST <= pduId <= FORTUNE_QUIT) )
			handleFortuneError(serviceSocket);
		state = protocol[state][pduId](serviceSocket);
	}
	return NULL;
}

int handleFortuneRequest(nmu_socket_t serviceSocket)
{
	char * fortunes[] = {
		"A man in a red flannel suit will visit you in December.\n",
		"1999 is sooooo last millenium.\n",
		"Answer hazy, ask again later.\n",
	};
	
	int myFortuneIndex = 0;
	
	pthread_mutex_lock(&fortuneMutex);
	myFortuneIndex = fortuneIndex++;
	pthread_mutex_unlock(&fortuneMutex);
	
	uint8_t	fortuneReply = FORTUNE_REPLY; 
	uint8_t count = (uint8_t)strlen(fortunes[myFortuneIndex % 3]);

	serviceSocket->write(serviceSocket, &fortuneReply, sizeof(uint8_t));
	count = strlen(fortunes[myFortuneIndex % 3]);
	serviceSocket->write(serviceSocket, &count, sizeof(uint8_t));
	serviceSocket->write(serviceSocket, fortunes[myFortuneIndex % 3], count);
	
	return RUNNING;
}

int handleFortuneQuit(nmu_socket_t serviceSocket)
{
	serviceSocket->close(serviceSocket);
	return DONE;
}

int handleFortuneError(nmu_socket_t serviceSocket)
{
	serviceSocket->error(serviceSocket, "fortuneServer: ERROR protocolError\n");
	return DONE;
}
