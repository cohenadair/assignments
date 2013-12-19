// Cohen Adair, CS201
// File to hold methods used throughout LLLibrary program.

#include <string>
using namespace std;

// Converts the given "s" string to lowercase.
string toLowercase (string s) {

	for (int i = 0; i < s.length(); i++)
		if (s[i] >= 'A' && s[i] <= 'Z')
			s[i] = s[i] + ('a' - 'A');

	return s;
}
