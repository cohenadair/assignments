/*
 * LLN.cpp
 *
 *  Created on: 2014-02-04
 *      Author: Cohen
 *
 *  Method file for the LLN class.
 */

#include <iostream>
#include <cstdlib>
#include <string>
#include "LLN.h"
using namespace std;

LLN::LLN(string s, LLN *n) {
	card = s;
	next = n;
}

LLN::~LLN() {
	delete next;
}

LLN * LLN::getnext() {
	return next;
}

void LLN::setnext(LLN *n) {
	next = n;
}

// prints the list
void LLN::print() {
	cout << card << endl;

	if (next != NULL)
		next->print();
}

// splits the list in two
// "this" is one list and the other is returned
LLN * LLN::split() {
	if (next == NULL)
		return NULL;

	LLN *res = getnext();
	setnext(res->getnext());

	if (next != NULL)
		res->setnext(next->split()); // calls split() recursively on every other node

	return res;
}

// merges two lists together
// "this" is one list and "b" is the other
// the head of the combined list is returned
LLN * LLN::merge(int len, LLN *b, int blen) {
	if (len == 0) return b;
	if (blen == 0) return this;

	int r = rand() % (len + blen) + 1; // between 1 and (len + blen)

	if (r <= len) {
		next = (next) ? next->merge(len - 1, b, blen) : b;
		return this;
	} else {
		b->setnext((b->getnext()) ? b->getnext()->merge(blen - 1, this, len) : this);
		return b;
	}
}

// returns the head of the shuffled list
LLN *LLN::shuffle(int len) {
	if (len <= 1)
		return this;

	LLN *tmp = split();
	LLN *thisList = NULL;

	int thisLength = (len + 1) / 2; // for an odd numbered length, "this" list is 1 node larger
	int tmpLength = len / 2;

	thisList = shuffle(thisLength);
	tmp = tmp->shuffle(tmpLength);

	return thisList->merge(thisLength, tmp, tmpLength);
}
