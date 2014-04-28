// Cohen Adair, CS222
// 13 April 2014
// Method file for the DB class.

#include <iostream>
#include "DB.h"

DB::DB() { 
	T = new RBTree(); 
}

DB::~DB() {	
	delete T; 
}

// returns a DRT of the data associated with "key"
DRT * DB::search(string key) {
	string data = "", next = "", prev = "";

	if (key == "") {
		data = "";
		next = T->first();
		prev = T->last();
	} else {
		string d = T->lookup(key);
		data = d;
		next = T->next(key);
		prev = T->prev(key);
	}

	return new DRT(data, next, prev);
}

// used to add, change, or delete entries in the database
DRT * DB::modify(string key, string data) {
	DRT *res = search(key);

	if (key != "") {
		string d = T->lookup(key);

		if (d == "" && data == "") {}
		else if ((d == "" || d >= "0") && data != "")
			T->add(key, data);
		else if (d != "" && data == "")
			T->remove(key);
		else if (d != "" && data != "") {
			T->remove(key);
			T->add(key, data);
		}
	}

	return res;
}
