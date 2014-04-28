// Cohen Adair, CS222
// 25 March 2014
// Main method file.

#include <iostream>
#include <fstream>
#include <string>
#include "main.h"
#include "Database.h"
#include "DB.h"
#include "DRT.h"
using namespace std;

int main(int argc, char **argv) {

	ifstream in ("PG4-1.in");
	Database *D = new DB();
	string cmd = "", file = "", priority = "";
	int entries = 0;

	while (cmd != "EXIT") {
		in >> cmd;
		
		if (cmd == "PRINT") {
			handlePrint(D);
			continue;
		}

		if (cmd == "SUBMIT") {
			in >> file >> priority;
			handleModify(D, ++entries, file, priority);
			continue;
		}

		if (cmd == "REMOVE") {
			in >> file;
			handleDelete(D, file);
			continue;
		}
	}

	system("pause");
	return 0;
}

// handles the print command
void handlePrint(Database *D) {
	DRT *info = D->search("");
	string first = info->getnext();
	info = D->modify(first, "");
	
	if (first == "")
		cout << "The print queue is empty" << endl;
	else
		cout << info->getdata() << " is printing" << endl;
}

// handles the modify command
void handleModify(Database *D, int entryNumber, string file, string priority) {
	D->modify(getKey(entryNumber, priority), file);
	cout << file << " has been submitted to the print queue with priority " << priority << endl;
}

// handles the delete command
void handleDelete(Database *D, string file) {
	int c = 0;
	
	DRT *info = D->search("");
	string key = info->getnext(); // get the first key in the database
	
	// traverse through tree, removing all instances of "file"
	while (key != "") {
		info = D->search(key);
	
		if (file == info->getdata()) {
			D->modify(key, "");
			c++;
		}

		key = info->getnext();
	}

	cout << c << " copies of " << file << " were removed" << endl;
}

// returns a 6-character string based on the entry number and priority level
// Example:
//		getKey(1, "30") will return "001030"
string getKey(int entryNumber, string priority) {
	string entries = to_string((long long)entryNumber);

	while (entries.length() < 3)
		entries = '0' + entries;

	while (priority.length() < 3)
		priority = '0' + priority;

	return priority + entries;
}
