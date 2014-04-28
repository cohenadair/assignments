/* Andrew A. Poe, CS222-01-14W Program 2, Main Program
   This program shuffles and prints a deck of playing cards. */

#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include "LL.h"
#include "PG2.h"
using namespace std;

int main (int argc, char **argv) {

	srand (time (NULL));
	LL *L = new LL ();
	string *rank = new string[13];

	rank[0] = "ACE";
	rank[1] = "TWO";
	rank[2] = "THREE";
	rank[3] = "FOUR";
	rank[4] = "FIVE";
	rank[5] = "SIX";
	rank[6] = "SEVEN";
	rank[7] = "EIGHT";
	rank[8] = "NINE";
	rank[9] = "TEN";
	rank[10] = "JACK";
	rank[11] = "QUEEN";
	rank[12] = "KING";

	string *suit = new string[4];
	suit[0] = "CLUBS";
	suit[1] = "DIAMONDS";
	suit[2] = "HEARTS";
	suit[3] = "SPADES";

	for (int i=0; i < 4; i++)
		for (int j=0; j < 13; j++)
			L->add (rank[j]+" OF "+suit[i]);

	L->shuffle ();
	L->print ();

	delete L;
	delete[] rank;
	delete[] suit;
	return 0;
}
