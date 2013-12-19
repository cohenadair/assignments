// Cohen Adair, CS201
// Method file for the LLN (Linked List Node) class.

#include <cstdlib>
#include <iostream>
#include "LLN.h"
using namespace std;

LLN::LLN (int n, LLN * nextNode) {

	value = n;
	count = 1;
	next = nextNode;
}

LLN::~LLN () {

	delete next;
}

// Helper method for LL->addTail().  
// Adds a node with value "n" to the end of the linked list.
// If the value already exists, will increment the existing node's count and will not create a new node.
void LLN::addTail(int n) {

	if (n == value) 
		count = count + 1;
	else if (next == NULL)
		next = new LLN (n, NULL);
	else
		next->addTail(n);
}

// Helper method for LL->print().
// Prints the linked list to the screen.
void LLN::print() {

	cout << "There are " << count << " of value " << value << "." << endl;

	if (next != NULL)
		next->print();
}
