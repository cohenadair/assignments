#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <netdb.h>

#include "fortune.h"

void handleOptions(int argc, char *argv[], char **hostNamePtr, char **portPtr);
int connectToServer(char *hostname, char *port);
void handleFortuneProtocol(int sockfd);
bool handleReply(int sockfd);

bool killServer = false;

void handleError(char *msg)
{
    fprintf(stderr, "%s\n", msg);
    exit(-1);
}

int main(int argc, char *argv[])
{
    int sockfd;
	char *portno;
	char *hostName;

	handleOptions( argc, argv, &hostName, &portno );
	sockfd = connectToServer( hostName, portno );
	handleFortuneProtocol(sockfd);

    return 0;
}

void handleOptions(int argc, char *argv[], char **hostNamePtr, char **portPtr)
{
    if ((argc != 3 && argc != 4) || atoi(argv[2]) <= 0)
    	handleError("ERROR: Invalid arguments\n"
    				"Usage: fortuneClient <hostname> <port>\nOR\n"
    			    "To kill server: fortuneClient <hostname> <port> k");

    killServer = (argc == 4) && (strcmp(argv[3], "k") == 0);

	*hostNamePtr = argv[1];
    *portPtr = argv[2];
}

int connectToServer(char *hostname, char *port)
{
	struct addrinfo *result = NULL;
	struct addrinfo *next = NULL;
	struct addrinfo hints;
	int	sockfd;

	memset(&hints, 0, sizeof(struct addrinfo));

	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	if (getaddrinfo(hostname, port, &hints, &result) != 0)
		handleError("ERROR getaddrinfo failed");

	// Run through available addresses, till a successful connection.
	for(next = result; next != NULL; next = next->ai_next) {
		// Open socket on this address.
		sockfd = socket(next->ai_family, next->ai_socktype, next->ai_protocol);

		if( sockfd == -1 )
			continue;

		// Connect to server..
		if(connect(sockfd, next->ai_addr, next->ai_addrlen) == -1){
			close(sockfd);
			continue;
		}

		// if we get here, successful connection
		break;
	}

	freeaddrinfo(result);

	if (sockfd < 0)
		handleError("ERROR creating socket");

	if (next == NULL)
		handleError("ERROR connecting to server");

	return sockfd;
}

void handleFortuneProtocol(int sockfd)
{
	uint8_t	pduId;
	int fortuneCount;

	// kill the server if specified by the user
	if (killServer) {
		pduId = FORTUNE_KILL;

		if (write(sockfd, &pduId, sizeof(uint8_t)) == -1)
			perror("Error writing FORTUNE_KILL");

		close(sockfd);
		handleError("Killed server.");
	}

	// gets 9 fortunes
	for (fortuneCount = 1; fortuneCount <= 9; fortuneCount++) {
		pduId = FORTUNE_REQUEST;

		if (write(sockfd, &pduId, sizeof(uint8_t)) == -1) {
			perror("Error writing pduId");
			break;
		}

		if (read(sockfd, &pduId, sizeof(uint8_t)) == -1) {
			perror("Error reading pduId");
			break;
		}

		if (pduId == FORTUNE_REPLY) {
			if (!handleReply(sockfd))
				break;
		} else {
			close(sockfd);
			handleError("Protocol violation");
		}
	}

	pduId = FORTUNE_QUIT;
	write(sockfd, &pduId, sizeof(uint8_t));
	close(sockfd);
}

bool handleReply(int sockfd)
{
	uint8_t	count;
	char	buffer[256];

	memset(buffer, 0, 256);

	if (read(sockfd, &count, sizeof(uint8_t)) == -1) {
		perror("Error reading count");
		return false;
	}

	if (read(sockfd, buffer, count) == -1) {
		perror("Error reading fortune");
		return false;
	}

	printf("%s", buffer);
	return true;
}
