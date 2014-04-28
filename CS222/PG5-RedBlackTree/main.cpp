// Cohen Adair, CS222
// 13 April 2014
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

	Database *D = new DB();
	string cmd = "", bookTitle = "";

	ifstream in ("PG5-1.in");
	//ofstream out ("PG5-mine.out");

	while (true) {
		in >> cmd;
		in.ignore();

		if (in.eof())
			break;

		if (cmd == "ADD") {
			getline(in, bookTitle);
			handleAdd(D, cout, bookTitle);
			continue;
		}
		
		if (cmd == "PRINT") {
			handlePrint(D, cout);
			continue;
		}

		if (cmd == "DELETE") {
			getline(in, bookTitle);
			handleDelete(D, cout, bookTitle);
			continue;
		}

		if (cmd == "COUNT") {
			handleCount(D, cout);
			continue;
		}
	}

	cout << "Thank you for using this program!" << endl;

	in.close();
	//out.close();

	system("pause");
	return 0;
}

// handles the add command
// adds a book to the library
void handleAdd(Database *D, ostream &o, string bookTitle) {
	DRT *info = D->search(bookTitle);
	string data = info->getdata();

	if (data != "") {
		int i = stoi(data);
		i++;
		data = to_string((long long)(i));
		D->modify(bookTitle, data);
	} else
		D->modify(bookTitle, "1");

	o << "One copy of " << bookTitle << " has been added to the library." << endl;
}

// handles the print command
// prints a list of books that are in the library and each book's number of copies
void handlePrint(Database *D, ostream &o) {
	DRT *info = D->search ("");
	string k = info->getnext();

	if (k == "") {
		o << "The library is empty." << endl;
		return;
	}

	while (k != "") {
		info = D->search(k);
		string d = info->getdata ();
		o << k << ": " << d << " copy(ies)" << endl;
		k = info->getnext();
	}		
}

// handles the delete command
// removes a book from the library
void handleDelete(Database *D, ostream &o, string bookTitle) {
	DRT *info = D->search(bookTitle);
	string data = info->getdata();

	if (data == "1") 
		D->modify(bookTitle, "");
	else if (data != "") {
		int i = stoi(data);
		i--;
		data = to_string((long long)(i));
		D->modify(bookTitle, data);
	} else {
		o << "This book is not in the library." << endl;
		return;
	}

	o << "One copy of " << bookTitle << " has been deleted from the library." << endl;
}

// handles the count command
// prints the total number of books in the library
void handleCount(Database *D, ostream &o) {
	int c = 0;
	DRT *info = D->search ("");
	string k = info->getnext();

	while (k != "") {
		info = D->search(k);
		string d = info->getdata ();
		c = c + stoi(d);
		k = info->getnext();
	}	

	o << "There are " << c << " books in the library." << endl;
}
