/* Andrew A. Poe, CS222-01-14W, Program 2
   Linked List Node Definitions */

#ifndef _LLN_
#define _LLN_

#include <string>
using namespace std;

class LLN {

 private:
  string card; //Name of playing card
  LLN *next; //The next node in the lsit

 public:
  LLN (string s, LLN *n); //Constructor
  ~LLN (); //Destructor
  LLN * getnext (); //Accessor
  void setnext (LLN *n); //Mutator
  void print (); //Prints nodes in linked list
  LLN * split (); //Splits the list in half recursively;
                  //"this" is one of the halves; the other half is
                  //returned
  LLN * merge (int len, LLN *b, int blen);
              //Merges "this" list with len elements with the b list of
              //blen elements.  The merge is accomplished randomly.
  LLN * shuffle (int len); //Puts list in random order
};

#endif
