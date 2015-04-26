//
//  EchoChat.h
//
//  Created by Cohen Adair on 03/02/2015.
//  CS442, Northern Michigan University
//

#ifndef ECHO_CHAT
#define ECHO_CHAT

#include <sys/types.h>
#include <sys/poll.h>
#include <sys/socket.h>
#include <netinet/in.h>	
#include <netdb.h>
#include <string.h>	
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <iostream>
#include <unistd.h>	

using namespace std;

#define MAX_CLIENTS 1000

int main(int argc, char *argv[]);
int broadcast(int fd, int fd_index, struct pollfd pollfds[], int fd_count);
int accept_client(int socket, struct pollfd pollfds[], int fd_count);
int make_server_socket(const char *port);
void error(const char *msg, bool cond);

#endif
