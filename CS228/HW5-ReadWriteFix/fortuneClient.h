#ifndef FORTUNE_CLIENT
#define FORTUNE_CLIENT

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdbool.h>
#include "NMUSocket.h"
#include "fortune.h"

void handleFortuneProtocol(nmu_socket_t pSocket);

#endif
