/*
 * LL.cpp
 *
 *  Created on: 2014-02-04
 *      Author: Cohen
 *
 *  Method file for the LL class.
 */

#include <iostream>
#include <cstdlib>
#include <string>
#include "LL.h"
using namespace std;

LL::LL() {
	head = NULL;
	size = 0;
}

LL::~LL() {
	delete head;
}

// prints the linked list
void LL::print() {
	if (head != NULL)
		head->print();
}

// adds a node to the front of the linked list
void LL::add(string s) {
	if (head == NULL)
		head = new LLN(s, NULL);
	else
		head = new LLN(s, head);

	size++;
}

// shuffles the list
void LL::shuffle() {
	if (head != NULL)
		head = head->shuffle(size);
}
