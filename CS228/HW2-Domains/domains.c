/*
 * domains.c
 *
 *  Created on: 2014-02-16
 *      Author: Cohen
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdbool.h>

struct hostent *getHostInfo();
void printOfficialName(struct hostent *h);
void printAliases(struct hostent *h);
void printIPs(struct hostent *h);

int main(int argc, char *argv[]) {

	struct hostent *pHost;

	while (true) {
		fprintf(stderr, "Enter a domain name: ");

		pHost = getHostInfo();
		if (pHost == NULL) {
			fprintf(stderr, "Could not get host info.\n");
			exit(-1);
		}

		printOfficialName(pHost);
		printAliases(pHost);
		printIPs(pHost);

		fprintf(stderr, "\n");
	}

	return 0;
}

struct hostent *getHostInfo() {

	int buffer_size = 256;
	char *input;
	char buffer[buffer_size];

	input = fgets(buffer, buffer_size, stdin);

	if (input == NULL) {
		fprintf(stderr, "Could not get input from user.\n");
		exit(-1);
	}

	if (strlen(input) == 1) {
		fprintf(stderr, "Finished.\n");
		exit(0);
	}

	input[strlen(input) - 1] = (int)NULL; // ?
	return gethostbyname(input);
}

void printOfficialName(struct hostent *h) {
	fprintf(stderr, "Official Name: %s\n", h->h_name);
}

void printAliases(struct hostent *h) {
	fprintf(stderr, "Aliases:\n");

	int i = 0;
	while (h->h_aliases[i] != NULL)
		fprintf(stderr, "\t%s\n", h->h_aliases[i++]);
}

void printIPs(struct hostent *h) {
	fprintf(stderr, "IP Addresses: \n");

	struct in_addr ipAddr;
	char **pIPAddr = h->h_addr_list;

	while (*pIPAddr != NULL) {
		ipAddr.s_addr = *(unsigned int *)pIPAddr++;
		fprintf(stderr, "\t%s\n", inet_ntoa(ipAddr));
	}
}
