/* Andrew A. Poe, CS222-01-14W Program 2
   Linked List Definitions */

#ifndef _LL_
#define _LL_

#include <string>
#include "LLN.h"
using namespace std;

class LLN;

class LL {

 private:
  LLN *head; //pointer to the head of the linked list
  int size;  //number of elements in the linked list

 public:
  void print (); //prints the linked list
  void add (string s); //adds an element to the head of the linked list
  void shuffle (); //puts linked list in random order
  LL (); //constructor
  ~LL (); //destructor
};

#endif
