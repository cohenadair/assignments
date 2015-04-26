//
//  EchoChat.c
//
//  Created by Cohen Adair on 03/02/2015.
//  CS442, Northern Michigan University
//

#include "EchoChat.h"

int main(int argc, char *argv[]) {
	error("Port number required. Usage: ./EchoChat 5000", argc <= 1);
	
	int socket = make_server_socket(argv[1]);
	int fd_count = 1, pollres;
	struct pollfd pollfds[MAX_CLIENTS];
	
	pollfds[0].fd = socket;
	pollfds[0].events = POLLIN;
	
	while (true) {
		pollres = poll(pollfds, fd_count, -1);
		cout << "Poll: " << pollres << endl;

		switch (pollres) {
			case 0: // poll timed out
				break;
			case -1:
				cout << "Poll error." << endl;
				break;
			default: {
				// accept new connection
				if (pollfds[0].revents & POLLIN) {
					fd_count = accept_client(socket, pollfds, fd_count);
					break;
				}
				
				cout << "Received something..." << endl;
				
				for (int i = 0; i < fd_count; i++) {
					if (pollfds[i].revents & POLLIN) {
						cout << "Found event message: ";
						fd_count = broadcast(pollfds[i].fd, i, pollfds, fd_count);
					}
				}
				
				break;
			}
		}	
	}
	
	close(socket);
	return 0;
}

// sends the content of fd to all clients in pollfds
int broadcast(int fd, int fd_index, struct pollfd pollfds[], int fd_count) {
	int result = fd_count;
	char buf[100000];
	
	int len = read(fd, buf, 100);
	if (len > 0) {
		buf[len] = 0;
		cout << buf << endl;
		
		for (int i = 1; i < fd_count; i++) {
			// broadcast to all who didn't type
			if (fd != pollfds[i].fd) {
				int w = write(pollfds[i].fd, buf, len);
				if (w == -1)
					cout << "Failed to write to fd: " << pollfds[i].fd << endl;
			}
		}
	} else {
		cout << "Unable to read." << endl;
		pollfds[fd_index] = pollfds[result - 1];
		result--;
	}
	
	return result;
}

// tries to accecpt and returns the new file descriptor count
int accept_client(int socket, struct pollfd pollfds[], int fd_count) {
	int result = fd_count;
	result++;
	
	if (result >= MAX_CLIENTS) {
		cout << "Too many clients." << endl;
		return --result;
	}
	
	cout << "Adding to index: " << result - 1 << endl;
	struct sockaddr_in sa;
	int sa_len = sizeof(sa);
	
	if (pollfds[result - 1].fd = accept(socket, (struct sockaddr *)&sa, (unsigned int *)&sa_len)) {
		pollfds[result - 1].events = POLLIN;
		cout << "Successfully added client." << endl;
	} else {
		cout << "Couldn't accept." << endl;
		result--;
	}
	
	return result;
}

int make_server_socket(const char *port) {
	const int MAXNAMELEN = 255;
	const int BACKLOG = 3;	
	char localhostname[MAXNAMELEN]; 
	int s; 		
	int len;
	struct sockaddr_in sa; 
	struct hostent *hp;
	struct servent *sp;
	int portnum;	
	int ret;

	gethostname(localhostname, MAXNAMELEN);
	hp = gethostbyname(localhostname);
	error("Failed to get hostname", hp == 0);
	
	sscanf(port, "%d", &portnum);
	if (portnum ==  0) {
		sp = getservbyname(port, "tcp");
		portnum = ntohs(sp->s_port);
	}
	sa.sin_port = htons(portnum);

	bcopy((char *)hp->h_addr, (char *) & sa.sin_addr, hp->h_length);
	sa.sin_family = hp->h_addrtype;

	s = socket(hp->h_addrtype, SOCK_STREAM, 0);
	error("Failed to create socket.", s == -1);
	
	ret = bind(s, (struct sockaddr *) & sa, sizeof(sa));
	error("Failed to bind.", ret == -1);
	
	listen(s, BACKLOG);
	cout << "Waiting for connection on port " << port << ", hostname " << localhostname << "." << endl;
	
	return s;
}

void error(const char *msg, bool cond) {
	if (!cond)
		return;
	
	cout << msg << endl;
	exit(1);
}
