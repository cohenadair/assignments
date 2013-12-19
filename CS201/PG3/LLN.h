// Cohen Adair, CS201
// Header file for the LLN (Linked List Node) class.

#ifndef _LLN_
#define _LLN_

using namespace std;

class LLN {
private:
	int value;
	int count; // ensures no duplicate nodes in the linked list
	LLN * next;
public:
	LLN(int n, LLN * nextNode);
	~LLN();
	void addTail(int n);
	void print();
};

#endif
