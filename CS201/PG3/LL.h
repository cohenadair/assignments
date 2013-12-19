// Cohen Adair, CS201
// Header file for the LL (Linked List) class.

#ifndef _LL_
#define _LL_

#include "LLN.h"
using namespace std;

class LLN;
class LL {
private:
	LLN * head;
public:
	LL ();
	~LL ();
	void addTail (int n);
	void print();
};

#endif
