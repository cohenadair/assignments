// Cohen Adair, CS201
// Method file for the ComparableArray class.

#include <string>
using namespace std;

#include "ComparableArray.h"

// Initializes the ComparableArray with size "i".
ComparableArray::ComparableArray (int s) {

	sz = s; 	
	CA = new Comparable *[sz];
}

// Frees the memory of the ComparableArray.
ComparableArray::~ComparableArray () {

	for (int i = 0; i <= sz; i++) { 
		delete CA[i];
		sz = sz - 1;
	}
}

// Returns the smallest Comparable object in the array.
Comparable * ComparableArray::smallest () {

	Comparable * res = CA[0];

	for (int i = 0; i < sz; i++)
		if (CA[i]->cmp(res) <= 0)
			res = CA[i];

	return res;
}

// Returns the largest Comparable object in the array.
Comparable * ComparableArray::largest () {

	Comparable * res = CA[0];

	for (int i = 0; i < sz; i++)
		if (CA[i]->cmp(res) >= 0)
			res = CA[i];

	return res;
}

// Sets the input element "index" of the ComparableArray to "c".
void ComparableArray::seti (int index, Comparable *c) {

	CA[index] = c;
}
