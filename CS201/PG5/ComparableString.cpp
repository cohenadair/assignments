// Cohen Adair, CS201
// Method file for the ComparableString class.

#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

#include "Comparable.h"
#include "ComparableString.h"

// Initializes a ComparableString object with text "s".
ComparableString::ComparableString (string S) {

	s = S;
}

// Compares the ComparableString to the Comparable object "c".  Comparison is case insensitive.
int ComparableString::cmp (Comparable *c) {

	string lowerS = s;
	string lowerC = ((ComparableString *)c)->gets();
	
	for (int i = 0; i < lowerS.length(); i++)
		if (lowerS[i] >= 'A' && lowerS[i] <= 'Z')
			lowerS[i] = lowerS[i] + ('a' - 'A');

	for (int i = 0; i < lowerC.length(); i++)
		if (lowerC[i] >= 'A' && lowerC[i] <= 'Z')
			lowerC[i] = lowerC[i] + ('a' - 'A');
	
	if (lowerS == lowerC) 
		return 0;

	if (lowerS > lowerC) 
		return 1;

	if (lowerS < lowerC)
		return -1;

	return NULL;
}

// Prints the text of the ComparableString.
void ComparableString::print() {

	cout << s;
}

// Returns the text of the ComparableString.
string ComparableString::gets() {

	return s;
}
