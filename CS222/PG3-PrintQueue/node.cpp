// Cohen Adair, CS222-01-14W
// Method file for the Node class.

#include <iostream>
#include <string>
#include "node.h"
using namespace std;

Node::Node(PrintJob *newJob, Node *newNext) {
	job = newJob;
	next = newNext;
}

Node::~Node() {
	delete job;
	delete next;
}

// returns the node's next node
Node *Node::getNext() {
	return next;
}

// sets the node's next to "new_next"
void Node::setNext(Node *newNext) {
	next = newNext;
}

// returns the node's PrintJob object
PrintJob *Node::getJob() {
	return job;
}

// prints the next node and this node to the screen
void Node::print() {
	cout << job->getTime() << endl;
	cout << job->getLength() << endl;
	cout << endl;

	if (next)
		next->print();
}

