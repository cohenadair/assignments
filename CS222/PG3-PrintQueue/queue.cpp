// Cohen Adair, CS222-01-14W
// Method file for the Queue class.

#include "queue.h"

Queue::Queue() {
	head = NULL;
	tail = NULL;
}

Queue::~Queue() {
	delete head;
	delete tail;
}

// adds a new print job to the queue
void Queue::ENQUEUE(PrintJob *newJob) {
	if (head) {
		tail->setNext(new Node(newJob, NULL));
		tail = tail->getNext();
	} else
		tail = head = new Node(newJob, NULL);
}

// removes, returns, and resets the current head node
PrintJob *Queue::DEQUEUE() {
	if (!head)
		return NULL;

	PrintJob *tmpJob = new PrintJob(head->getJob()->getTime(), head->getJob()->getLength());
	Node *tmpHead = head;

	// remove head from queue
	head = head->getNext();
	tmpHead->setNext(NULL);

	delete tmpHead;
	return tmpJob;
}

// returns true if the queue is empty
bool Queue::ISEMPTY() {
	return (!head);
}

// prints the queue to the screen
void Queue::print() {
	if (head)
		head->print();
}
