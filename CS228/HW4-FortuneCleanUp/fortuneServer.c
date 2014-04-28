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
#include <arpa/inet.h>
#include <netdb.h>
#include "fortune.h"

int handleAccept(int sockfd);
int handleBinding(char *portno);
void handleFortuneServerProtocol(int sockfd);

void handleError(char *msg)
{
    fprintf(stderr, "%s\n", msg);
    exit(-1);
}

void handleOptions( int argc, char *argv[], char **portnoPtr)
{
    if (argc < 2 || atoi(argv[1]) <= 0)
        handleError("ERROR, no port provided or invalid port number.\n"
        		    "Usage: fortuneServer <port>");

    *portnoPtr = argv[1];
}

int main(int argc, char *argv[])
{
	int sockfd, newsockfd;
	char *portno;

	handleOptions(argc, argv, &portno);

	sockfd = handleBinding(portno);

	// Listen for connection requests.
	if (listen(sockfd, 5) < 0) {
		close(sockfd);
		handleError("ERROR on listen");
	}

	while (true) {
		newsockfd = handleAccept(sockfd);
		handleFortuneServerProtocol(newsockfd);
		close(newsockfd);
	}

	close(sockfd);
	return 0;
}

int handleAccept(int sockfd)
{
	int newsockfd, clilen;
	struct sockaddr_in serv_addr, cli_addr;

	// Accept a connection.
	clilen = sizeof(cli_addr);

	newsockfd = accept(
		sockfd,
		(struct sockaddr *)&cli_addr,
		(socklen_t *)&clilen);

	if (newsockfd < 0) {
		close(sockfd);
		handleError("ERROR on accept");
	}

	return newsockfd;
}

int handleBinding(char *portno)
{
	int sockfd;
	struct addrinfo *result = NULL;
	struct addrinfo *p = NULL;
	struct addrinfo hints;

	memset(&hints, 0, sizeof(struct addrinfo));

	hints.ai_flags = AI_PASSIVE;
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	if (getaddrinfo(NULL, portno, &hints, &result) != 0)
		handleError("ERROR in getaddrinfo()");

	// loop through linked list until a successful bind is made
	for (p = result; p != NULL; p = p->ai_next) {
		sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);

		if (sockfd == -1)
			continue;

		if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
			close(sockfd);
			continue;
		}

		// break if both creating socket and binding are successful
		break;
	}

	freeaddrinfo(result);

	if (sockfd < 0)
		handleError("ERROR creating socket");

	if (p == NULL) {
		close(sockfd);
		handleError("ERROR binding to port");
	}

	return sockfd;
}

static char * fortunes[] = {
	"A man in a red flannel suit will visit you in December.\n",
	"1999 is sooooo last millenium.\n",
	"Answer hazy, ask again later.\n",
};

void handleFortuneServerProtocol(int sockfd)
{
	static int state;
	uint8_t pduId;

	state = RUNNING;

	while (state != DONE) {
		if (read(sockfd, &pduId, sizeof(uint8_t)) == -1) {
			perror("Error reading socket");
			break;
		}

		switch( pduId ){
		case FORTUNE_REQUEST:
			state = handleFortuneRequest(sockfd);
			break;
		case FORTUNE_QUIT:
			state = handleFortuneQuit(sockfd);
			break;
		case FORTUNE_KILL:
			close(sockfd);
			handleError("Killed by client.");
			break;
		default:
			close(sockfd);
			handleError("ERROR during protocol");
			break;
		}
	}
}

int handleFortuneRequest(int sockfd)
{
	static int fortuneIndex = 0;
	uint8_t	fortuneReply = FORTUNE_REPLY;
	uint8_t count = (uint8_t)strlen(fortunes[fortuneIndex % 3]);

	if (write(sockfd, &fortuneReply, sizeof(uint8_t)) == -1) {
		perror("Error writing FORTUNE_REPLY");
		return DONE;
	}

	count = strlen(fortunes[fortuneIndex % 3]);

	if (write(sockfd, &count, sizeof(uint8_t)) == -1) {
		perror("Error Writing count");
		return DONE;
	}

	if (write(sockfd, fortunes[fortuneIndex++ % 3], count) == -1) {
		perror("Error Writing Fortune");
		return DONE;
	}

	return RUNNING;
}

int handleFortuneQuit(int sockfd)
{
	close(sockfd);
	return DONE;
}
