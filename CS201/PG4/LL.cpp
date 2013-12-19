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

// Adds a node with title "s" in alphabetical order to the linked list.
void LL::add(string s) {

	if (head == NULL)
		head = new LLN (s, NULL);
	else
		if (s < head->getTitle()) { 
			LLN * P = head;
			head = new LLN(s, P);
		} else
			head->add(s);
}

// Removes all nodes from the linked list that have the substring "s".
void LL::remove(string s) {

	if (head != NULL)
		head = head->remove(s);
}

// Prints the linked list to the screen.
void LL::print() {

	if (head != NULL)
		head->print();

	cout << endl;
}
