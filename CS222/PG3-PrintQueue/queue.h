// Cohen Adair, CS222-01-14W
// Header file for the Queue class.

#ifndef _QUEUE_
#define _QUEUE_

#include "node.h"

class Node;

class Queue {

private: 
	Node *head;
	Node *tail;

public:
	Queue();
	~Queue();
	void ENQUEUE(PrintJob *newJob);
	PrintJob *DEQUEUE();
	bool ISEMPTY();
	void print();

};

#endif
