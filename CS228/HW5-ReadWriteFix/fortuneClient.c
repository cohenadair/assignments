#include "NMUSocket.h"
#include "fortuneClient.h"

void handleOptions(int argc, char *argv[], char **hostNamePtr, char **portPtr);
bool shouldQuit(void);
int handleFortuneReply(nmu_socket_t pSocket);

int main(int argc, char *argv[])
{
    nmu_socket_t pSocket;
	char *portno;
	char *hostName;

	handleOptions( argc, argv, &hostName, &portno ); 
	socketFactory.initialize();
	pSocket = socketFactory.connectTCPForHostnameAndPort( hostName, portno );
	handleFortuneProtocol(pSocket);
    return 0;
}

void handleOptions(int argc, char *argv[], char **hostNamePtr, char **portPtr)
{
    if (argc != 3) {
       fprintf(stderr,"usage: %s hostname port\n", argv[0]);
       exit(0);
    }
	*hostNamePtr = argv[1];
    *portPtr = argv[2];
}
void handleFortuneProtocol(nmu_socket_t pSocket)
{
	uint8_t	protocolState = RUNNING;
	uint8_t	pduId;

	pduId = FORTUNE_REQUEST;
	pSocket->write(pSocket, &pduId, sizeof(uint8_t));

	while(protocolState != DONE){
		pSocket->read(pSocket, &pduId, sizeof(uint8_t));
		switch(pduId){
		case FORTUNE_REPLY:
			protocolState = handleFortuneReply(pSocket);
			break;
		default:
			pSocket->error(pSocket, "ERROR: protocol error\n");
		}
		if(protocolState == DONE)
			break;
	} 
}

int handleFortuneReply(nmu_socket_t pSocket)
{
	uint8_t pduId;
	uint8_t	count;
	char	buffer[256];

	memset(buffer, 0, 256);
	pSocket->read(pSocket, &count, sizeof(uint8_t));
	pSocket->read(pSocket, buffer, count);
	printf("%s", buffer);
	if( shouldQuit() ){
		pduId = FORTUNE_QUIT;
		pSocket->write(pSocket, &pduId, sizeof(uint8_t));
		pSocket->close(pSocket);
		return DONE;
	} else {
		pduId = FORTUNE_REQUEST;
		usleep(1000000);
		pSocket->write(pSocket, &pduId, sizeof(uint8_t));
		return RUNNING;
	}
}


bool shouldQuit(void)
{
	static	int fortuneCount = 0;
	return (fortuneCount++ >= 9);
}
