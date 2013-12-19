// Cohen Adair, CS201
// Method file for the LLN (Linked List Node) class.

#include <cstdlib>
#include <iostream>
#include <string>
#include "LLN.h"
#include "libcohen.h"
using namespace std;

LLN::LLN (string s, LLN * nextNode) {

	title = s;
	next = nextNode;
}

LLN::~LLN () {

	delete next;
}

// Returns the title of book.
string LLN::getTitle() {

	return title;
}

// Helper method for LL->add().  
// Adds a node with title "s" to the linked list.  Adds the node in alphabetical order.
// If the title already exists, it will not be added.
void LLN::add(string s) {

	string lowerS = toLowercase(s);
	string lowerTitle = toLowercase(title);

	// if title already exists, don't add it
	if (lowerS == lowerTitle)
		return;

	if (next == NULL) 
		next = new LLN(s, NULL);
	else 
		if (lowerS > lowerTitle && lowerS < toLowercase(next->getTitle())) {
			LLN * P = next;
			next = new LLN (s, P);
		} else
			next->add(s);
}

// Helper method for LL->remove().
// Removes from the linked list all nodes that have the substring "s".
LLN * LLN::remove(string s) {

	if (next != NULL)
		next = next->remove(s);

	if (toLowercase(title).find(toLowercase(s)) != string::npos) {
		LLN * P = next;
		next = NULL;
		delete this;
		return P;
	} else
		return this;
}

// Helper method for LL->print().
// Prints the linked list to the screen.
void LLN::print() {

	cout << title << endl;

	if (next != NULL)
		next->print();
}
