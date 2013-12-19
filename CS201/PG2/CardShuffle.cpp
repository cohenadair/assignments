// Cohen Adair, CS201
// Shuffles and deals two 52-card decks.  Prints the average number of same cards when finished.

#include <iostream>
#include <string>
#include <ctime>
#include "CardShuffle.h";

using namespace std;

int main (int argc, char **argv) {

	srand(time(NULL));

	string *deckOne = new string[52];
	string *deckTwo = new string[52];

	string suits[4] = {"Hearts", "Diamonds", "Spades", "Clubs"};
	string values[13] = {"Ace", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King"};

	int c = 0;

	// assign the deck variables
	for (int i = 0; i < 4; i++) 
		for (int j = 0; j < 13; j++) {
			deckOne[c] = deckTwo[c] = values[j] + " of " + suits[i];
			c = c + 1;
		}

	const int TIMES_TO_RUN = 100;
	int *matches = new int[TIMES_TO_RUN];

	for (int i = 0; i < TIMES_TO_RUN; i++) {

		deckOne = shuffleDeck(deckOne); 
		deckTwo = shuffleDeck(deckTwo);

		matches[i] = 0;

		// deal the cards and print the results
		for (int j = 0; j < 52; j++) 
			if (deckOne[j] == deckTwo[j]) {
				cout << deckOne[j] << " / " << deckTwo[j] << ", MATCH" << endl;
				matches[i] = matches[i] + 1;
			} else
				cout << deckOne[j] << " / " << deckTwo[j] << endl;

		cout << "" << endl;
		cout << "There are " << matches[i] << " matches." << endl;
		cout << "" << endl;
	}

	cout << "Average matches after " << TIMES_TO_RUN << " cycles: " << average(matches, TIMES_TO_RUN) << endl;
	cout << "" << endl;

	delete[] deckOne;
	delete[] deckTwo;
	delete[] matches;

	system("pause");
	return 0;
}

// Copies the 'deck' argument, shuffles the copy, and returns it.
string * shuffleDeck (string *deck) {

	string *res = new string[52];

	// copy 'deck' into an array to return
	for (int i = 0; i < 52; i++) 
		res[i] = deck[i];

	// loop through each element, swapping it with another random element
	for (int i = 0; i < 52; i++) {
		int r = rand() % (i + 1);
		
		// swap the elements
		string tmp = res[i];
		res[i] = res[r];
		res[r] = tmp;
	}

	return res;
}

// Returns the average of the elements in 'arr' with length 'len'.
float average (int *arr, int len) {

	int sum = 0;

	for (int i = 0; i < len; i++) 
		sum = sum + arr[i];

	return ((float)sum / (float)len);

}
