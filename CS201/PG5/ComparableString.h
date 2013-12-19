//Andrew A. Poe, Professor, CS201-01-13F
//Northern Michigan University (Marquette Co, MI)
//ComparableString definitions

#ifndef _COMPARABLESTRING_
#define _COMPARABLESTRING_

#include <string>
#include "Comparable.h"
using namespace std;

class Comparable;
class ComparableString:public Comparable {
private:
 string s; //String stored in object
public:
 ComparableString (string S); //Constructor
 virtual int cmp (Comparable *c); //Inherited from Comparable
 virtual void print (); //Inherited from Comparable
 string gets(); //Retrieves string
};

#endif