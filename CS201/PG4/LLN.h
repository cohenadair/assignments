// Cohen Adair, CS201
// Header file for the LLN (Linked List Node) class.

#ifndef _LLN_
#define _LLN_

#include <string>
using namespace std;

class LLN {
private:
	string title;
	LLN * next;
public:
	LLN(string s, LLN * nextNode);
	~LLN();
	string getTitle();
	void add(string s);
	LLN * remove(string s);
	void print();
};

#endif
