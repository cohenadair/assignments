//Andrew A. Poe, Professor, CS201-01-13F
//Northern Michigan University (Marquette Co, MI)
//ComparableArray definitions

#ifndef _COMPARABLEARRAY_
#define _COMPARABLEARRAY_

#include "Comparable.h"

class Comparable;
class ComparableArray {
private:
 Comparable **CA;  // Array of Comparable pointers
 int sz; // number of elements in array
public:
 ComparableArray (int s); // initializes array with size s
 ~ComparableArray (); //destroys array and everything in it
 Comparable * smallest (); //retrieves smallest item in array
 Comparable * largest (); //retrieves largest item in array
 void seti (int i,Comparable *c); //puts c in item i of array

};

#endif