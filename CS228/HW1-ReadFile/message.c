#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include "message.h"

#define INPUT_FILE_NAME "input"

void handleFileError(FILE *pFile, char * msg);
void readNextCommand(FILE *pFile, cmd_frame_t *cmd_frame);
void processLoadStrings(FILE *pFile, unsigned int count);
void processPrintString(FILE *pFile, unsigned int index);
void processQuit(FILE *pFile, unsigned int index);
void freeTable(void);

char **stringTable;

int main(int argc, char *argv[]) {
	FILE *pFile;
	cmd_frame_t next_command;

	if ((pFile = fopen(INPUT_FILE_NAME, "rb")) == NULL) {
		fprintf(stderr, "Could not open the file %s", INPUT_FILE_NAME);
		exit(-1);
	}

	bool running = true;

	while (running) {
		readNextCommand(pFile, &next_command);

		switch (next_command.cmd) {
			case loadStrings:
				processLoadStrings(pFile, next_command.arg.count);
				break;
			case printString:
				processPrintString(pFile, next_command.arg.index);
				break;
			case quit:
				processQuit(pFile, next_command.arg.index);
				running = false;
				break;
		}
	}

	freeTable();
	return 0;
}

void handleFileError(FILE *pFile, char * msg) {
	fprintf(stderr, "%s\n", msg);
	fclose(pFile);
	exit(-1);
}

void readNextCommand(FILE *f, cmd_frame_t *cmd_frame) {
	unsigned int tmp;

	// read in and set the cmd field
	if (fread(&tmp, sizeof(unsigned int), 1, f) <= 0) {
		fprintf(stderr, "Could not read next command");
		exit(-1);
	}

	cmd_frame->cmd = htonl(tmp);

	// read in a set the arg.count/index field
	if (fread(&tmp, sizeof(unsigned int), 1, f) <= 0) {
		fprintf(stderr, "Could not read next command count/index");
		exit(-1);
	}

	cmd_frame->arg.count = htonl(tmp);
}

// loads the strings into a global array
void processLoadStrings(FILE *pFile, unsigned int count) {
	char *nextString;
	unsigned char byteCount;
	int bytesRead;
	int index;

	stringTable = (char **)calloc(sizeof(char *), count + 1); // why is this needed? when to call free()?

	for (index = 0; index < count; index++) {
		nextString = (char *)calloc(sizeof(char), byteCount + 1); // +1 for end of string char

		fread(&byteCount, sizeof(unsigned char), 1, pFile);
		bytesRead = fread(nextString, sizeof(char), byteCount, pFile);

		if (bytesRead != byteCount)
			handleFileError(pFile, "Did not read enough bytes for index "+index);

		stringTable[index] = nextString;
	}
}

void processPrintString(FILE *pFile, unsigned int index) {
	fprintf(stderr, "%s", stringTable[index]);
}

void processQuit(FILE *pFile, unsigned int index) {
	fprintf(stderr, "End Run: %s", stringTable[index]);
}

void freeTable() {
	int i = 0;

	while (stringTable[i] != NULL)
		free(stringTable[i++]);
//	char **nextString = stringTable;
//	while( *nextString != NULL ) free(*nextString++));
	free(stringTable);
}
