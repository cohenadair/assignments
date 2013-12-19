// Cohen Adair, CS201
// Stores input integers and strings in an object array and prints the smallest and largest to the screen.

#include <cstdlib>
#include <iostream>
#include <string>
using namespace std;

#include "ComparableArray.h"
#include "ComparableInt.h"
#include "ComparableString.h"

int main (int argc, char **argv) {

	string inputTypes[2] = {"integer", "string"}; // saves some repeated code
	string s = "";
	int arrayLength = 0;

	for (int k = 0; k <= 1; k++) {

		cout << "How many " << inputTypes[k] << "s? ";
		getline(cin, s);
		arrayLength = atoi(s.c_str());

		ComparableArray * tmp = new ComparableArray(arrayLength);

		for (int i = 0; i < arrayLength; i++) {

			cout << "Enter an " << inputTypes[k] << ": ";
			getline(cin, s);

			// adds the appropriate type of Comparable
			if (k == 0)
				tmp->seti(i, new ComparableInt(atoi(s.c_str())));
			else
				tmp->seti(i, new ComparableString(s));
		}

		cout << "" << endl;
		cout << "The largest " << inputTypes[k] << " is "; tmp->largest()->print(); cout << " and the smallest is "; tmp->smallest()->print(); cout << "." << endl;

		cout << "" << endl;
		delete tmp;
	}

	system("pause");
	return 0;
}
