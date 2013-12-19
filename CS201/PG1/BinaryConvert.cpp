// Cohen Adair, CS201
// Asks the user for a binary number.  Prints the input as well as it's decimal equivalent. 

#include <iostream>
#include <string>

#include "BinaryConvert.h"

using namespace std;

int main (int argc, char **argv) {

	string s;

	while (true) {

		cout << "Enter a binary number: ";

		getline(cin, s);

		if (!isStringBinary(s)) 
			continue;

		cout << "Binary:  " << s << endl;
		cout << "Decimal: " << convertBinaryString(s) << endl;

		break;
	}

	system("pause");
	return 0;
}

// Returns true if the string 's' is a binary number.
bool isStringBinary(string s) {

	// check for an empty string
	if (s == "") {
		cout << "Invalid input, try again." << endl;
		return false;
	}

	for (int i = 0; i < s.length(); i++)
		if (!(s[i] == '0') && !(s[i] == '1')) { // only 0's and 1's are valid
			cout << "Invalid input, try again." << endl;
			return false;
		}

	return true;
}

// Returns the decimal form of the binary string 's' as a string.
string convertBinaryString(string s) {

	string res = "";

	for (int i = 0; i < s.length(); i++) {
		res = addStrings(res, res); // double result
		if (s[i] == '1')
			res = addStrings(res, "1");
	}
		
	return res;
}

// Returns the sum of the strings 'a' and 'b'.
string addStrings(string a, string b) {

	// add 0's to make strings the same length
	while (a.length() < b.length())
		a = "0" + a;

	while (b.length() < a.length())
		b = "0" + b;

	a = "0" + a; // in case of carry
	b = "0" + b;

	int carry = 0;
	string res;

	for (int i = a.length() - 1; i >= 0; i--) {
		int s = (a[i] - '0') + (b[i] - '0') + carry;
		carry = s / 10; // s > 10, set carry to 1
		int d = s % 10; // get remainder
		res = ((char)(d + '0')) + res;
	}

	// remove excess 0's
	while (res.length() > 1 && res[0] == '0')
		res = res.substr(1);

	return res;
}
