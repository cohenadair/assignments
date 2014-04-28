#ifndef NMU_SOCKET
#define NMU_SOCKET

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

typedef struct in_addr IPAddress;
typedef struct sockaddr_in SocketAddress, *pSocketAddress;;

typedef struct NMUSocket *nmu_socket_t;

// Typedefs for the different function signatures needed.
// Function typenames have the prefix pFun.
// The suffix is the return value type code followed by the arg type codes.
// The type codes are:
//	V	void
//	B	bool
//	A	in_addr_t
//	S	nmu_socket_t
//	I	int
//	M	char *
typedef bool (*pFunBV)(void);
typedef nmu_socket_t (*pFunSV)(void);
typedef nmu_socket_t (*pFunSMP)(char *, short);
typedef nmu_socket_t (*pFunSMM)(char *, char *);
typedef void (*pFunVS)(nmu_socket_t);
typedef void * (*pFunPVS)(nmu_socket_t);
typedef int (*pFunIS)(nmu_socket_t);
typedef nmu_socket_t (*pFunSS)(nmu_socket_t);
typedef int (*pFunISMI)(nmu_socket_t, void *, int);
typedef void (*pFunVSM)(nmu_socket_t, char *);
typedef void (*pFunPVSH)(nmu_socket_t, pFunPVS);
typedef void * (*pFunThread)(void *);

// Socket Factory
//	Responsible for creating new sockets for clients and servers.
//	To create a server socket:
//		NMUSocketFactory.serveTCPForHostnameAndPort('euclid.nmu.edu', 8080);
//	To create a client socket:
//		NMUSocketFactory.connectTCPForHostnameAndPort('euclid.nmu.edu', 8080);

typedef struct
{
	// public
	pFunSMP serveTCPForHostnameAndPort;
	pFunSMM connectTCPForHostnameAndPort;
	// private
	pFunBV	initialize;
	pFunSV	new;
	bool	initialized;
} NMUSocketFactory;

extern NMUSocketFactory socketFactory;

// class NMUSocket
//	instance variables
//		SocketAddress	sockAddr;
//		int				sockfd;
//	methods
//		nmu_socket_t accept(nmu_socket_t);
//		void acceptAndServe(nmu_socket_t, pFunPVS);
//		int	read(nmu_socket_t, void *, int);
//		int	write(nmu_socket_t, void *, int);
//		void close(nmu_socket_t);
//		void error(nmu_socket_t, char *);
typedef struct NMUSocket
{
	pFunSS			accept;
	pFunPVSH		acceptAndServe;
	pFunISMI		read;
	pFunISMI		write;
	pFunVS			close;
	pFunVSM			error;
	SocketAddress	sockAddr;
	int sockfd;
} NMUSocket;

#endif
