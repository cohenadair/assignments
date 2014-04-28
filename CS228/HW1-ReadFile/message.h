#ifndef MESSAGE_H
#define MESSAGE_H

// Homework Assignment 1.
// The file input contains a typical stream of commands that would be sent over a socket.
// The program should open the input file for read binary.
// Initialize a boolean called, running, to true.
// While true,
//	read a command (int values are in network order)
//	process that command
// Close the input file

// Protocol
//	The protocol consists of three commands
//		loadStrings( count )
//			read <count> number of strings into an array
//			followed by <count> counted strings
//		printString( index )
//			print the string at <index> in the array of strings
//		quit( index )
//			print the message End Run: <string at index>
//			set running to false

// Command Codes
typedef enum
{
	loadStrings = 1,
	printString = 2,
	quit = 3
} cmd_t;

// Command Frame Header
typedef struct
{
	unsigned int cmd;
	union {
		unsigned int count;
		unsigned int index;
	} arg;
} cmd_frame_t;

// Counted String
#define VARYING 1

typedef struct
{
	unsigned char 	count;
	char			string[VARYING];
} countedString_t;

#endif
