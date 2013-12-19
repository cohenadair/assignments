//Andrew A. Poe, Professor, CS201-01-13F
//Northern Michigan University (Marquette Co, MI)
//ComparableInt definitions

#ifndef _COMPARABLEINT_
#define _COMPARABLEINT_

#include "Comparable.h"

class Comparable;
class ComparableInt:public Comparable {
private:
 int i; //The integer stored in the object

public:
 ComparableInt (int I); //Constructor
 virtual int cmp (Comparable *c); //Inherited from Comparable
 virtual void print (); //Inherited from Comparable
 int geti(); //retrieves integer
};

#endif