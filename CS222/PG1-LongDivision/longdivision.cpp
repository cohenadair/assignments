// Cohen Adair, CS222
// Main file.

#include <iostream>
#include <string>
#include "longdivision.h"
using namespace std;

int main(int argc, char **argv) {

	string input, result = "";

	cout << "Enter a numerator: ";
	getline(cin, input);
	int numerator = stoi(input);
	int origNumerator = numerator; // used to print the result

	cout << "Enter a denominator: ";
	getline(cin, input);
	int denominator = stoi(input);

	if (denominator == 0) {
		cout << "Can't divide by 0." << endl;
		return 0;
	}

	int * remainders = new int[denominator]; // remainder can't be larger than the largest input value
	for (int i = 0; i < denominator; i++) 
		remainders[i] = NULL;

	int count = 1;
	
	int remainder = numerator % denominator;
	remainders[remainder] = count;

	if (remainder == 0) 
		result = to_string((long long)(numerator / denominator)); // cast to long long; there's some bug with taking an int parameter; it doesn't recognize there's an int overload of to_string()
	else {
		result = to_string((long long)(numerator / denominator)) + ".";
		int tmpResLen = result.length() - 1; // used to () are always inserted after the "."

		while (true) {
			numerator = remainder * 10;
			count++;

			result = result + to_string((long long) (numerator / denominator)); 

			remainder = numerator % denominator;

			if (remainder == 0)
				break;

			if (remainders[remainder] == NULL) 
				remainders[remainder] = count; // needed to insert paranthesis later			
			else {
				result.insert(tmpResLen + remainders[remainder], "(");
				result.insert(result.length(), ")");
				break;
			}
		}
	}

	cout << origNumerator << "/" << denominator << " = " << result << endl;

	delete[] remainders;
	return 0;
}
