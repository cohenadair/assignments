// Cohen Adair, CS201
// Method file for the LL (Linked List) class. 

#include <cstdlib>
#include <iostream>
#include "LL.h"
using namespace std;

LL::LL() {

	head = NULL;
}

LL::~LL() {

	delete head;
}

// Adds a node with value "n" to the end of the linked list.
void LL::addTail(int n) {

	if (head == NULL)
		head = new LLN (n, NULL);
	else
		head->addTail(n);
}

// Prints the linked list to the screen.
void LL::print() {

	cout << endl;

	if (head != NULL)
		head->print();

	cout << endl;
}
