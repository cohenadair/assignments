// Cohen Adair, CS222-01-14W
// Header file for the Node class.

#ifndef _NODE_
#define _NODE_

#include <string>
#include "printjob.h"
using namespace std;

class Node {

private:
	PrintJob *job;
	Node *next;

public:
	Node(PrintJob *newJob, Node *newNext);
	~Node();
	Node *getNext();
	void setNext(Node *newNext);
	PrintJob *getJob();
	void print();

};

#endif
