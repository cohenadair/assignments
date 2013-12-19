// Cohen Adair, CS201
// Header file for the LL (Linked List) class.

#ifndef _LL_
#define _LL_

#include "LLN.h"
#include <string>
using namespace std;

class LLN;
class LL {
private:
	LLN * head;
public:
	LL();
	~LL();
	void add(string s);
	void remove(string s);
	void print();
};

#endif
