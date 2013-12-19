// Cohen Adair, CS201
// Method file for the ComparableInt class.

#include <iostream>
#include <cstdlib>
using namespace std;

#include "Comparable.h"
#include "ComparableInt.h"

// Initializes a ComparableInt object with value "i".
ComparableInt::ComparableInt (int I) {

	i = I;
}

// Compares the ComparableInt object to the Comparable obejct "c".
int ComparableInt::cmp (Comparable *c) {

	if (i == ((ComparableInt *)c)->geti()) 
		return 0;

	if (i > ((ComparableInt *)c)->geti()) 
		return 1;

	if (i < ((ComparableInt *)c)->geti()) 
		return -1;

	return NULL;
}

// Prints the ComparableInt object's value field.
void ComparableInt::print() {

	cout << i;
}

// Returns the ComparableInt object's value field.
int ComparableInt::geti() {

	return i;
}
