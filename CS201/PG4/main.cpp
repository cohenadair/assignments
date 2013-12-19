// Cohen Adair, CS201
// Adds input integers to a linked list and prints the linked list to the screen. 

#include <cstdlib>
#include <string>
#include <iostream>
#include "main.h"
#include "LL.h"
#include "libcohen.h"
using namespace std;

int main (int argc, char **argv) {

	LL * library = new LL();
	string s = ""; 
	string command = "";
	
	while (true) {

		cin >> command;
		command = toLowercase(command);

		if (command == "exit")
			break;

		if (command == "print") {
			library->print();
			continue;
		}

		getline(cin, s);
		s = s.substr(2, s.length() - 3); // removes the space at the beginning, and the end of line char and quote

		if (command == "add")
			library->add(s);

		if (command == "remove")
			library->remove(s);
	}

	delete library;

	system("pause");
	return 0;
}
