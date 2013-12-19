// Cohen Adair, CS201
// Adds input integers to a linked list and prints the linked list to the screen. 

#include <cstdlib>
#include <string>
#include <iostream>
#include "main.h"
#include "LL.h"
using namespace std;

int main (int argc, char **argv) {

	LL * numberList = new LL();
	string input = "";
	int c = 1;
	
	while (true) {

		cout << "Enter integer " << c << ":  ";
		getline(cin, input);

		if (input == "")
			break;

		numberList->addTail(stoi(input));

		c = c + 1;
	}

	numberList->print();
	delete numberList;

	system("pause");
	return 0;
}
