// Cohen Adair, CS201
// Main file.

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include "main.h"
using namespace std;

int main (int argc, char **argv) {

	cout << "Enter a file name: ";

	string fileName = "";
	getline(cin, fileName);

	fstream f (fileName, ios::in|ios::out|ios::binary);

	f.seekp(0, ios::end);
	int fileLength = f.tellg();

	char tmp[5];
	f.seekp(0);
	f.get(tmp, 5);
	int recordLength = getRecordLength(tmp, 4);

	shellSort(f, recordLength, (fileLength - 4) / recordLength);

	f.close();
	system("pause");
	return 0;
}

// Uses the shell sort algorithm to sort the records in the file 'f' in ASCII order.
void shellSort (fstream& f, int rLen, int r) {

	string r1 = "", r2 = "";

	int d = r; 
	while (d > 1) {
		if (d==2) d = 1;  
		else if (d%2==1) d = (d+1)/2;
		else if (d%4==0) d = d/2+1;
		else d = d/2+2;

		for (int i=d; i < r; i++)
			for (int j=i-d; j >= 0; j-=d) {

				r1 = getRecord(f, rLen, j);
				r2 = getRecord(f, rLen, j+d);
				
				if (r1 <= r2) 
					break;
				
				swapRecords(f, rLen, j, j+d, r1, r2);
			}
	}
}

// Returns the record length based on a char array of length n.
int getRecordLength(char * A, int n) {

	string s = "";
	int k = 0;

	while (A[k] == '0')
		k++;	

	for (int i = k; i < n; i++) 
		s += A[i];

	return stoi(s);
}

// Returns the "rth" record.  Each record has length "rLen".
string getRecord(fstream& f, int rLen, int r) {

	int i = 0;
	char c;
	string res = "";
	f.seekp(rLen*r + 4);

	while (i < rLen) {
		f.get(c);
		res += c;
		i++;
	}

	return res;
}

// Swaps the "n1st" record with "r2" and the "n2nd" record with "r1".
void swapRecords(fstream& f, int rLen, int n1, int n2, string r1, string r2) {

	f.seekp(n1*rLen + 4);
	for (int i = 0; i < rLen; i++) 
		f.put(r2[i]);

	f.seekp(n2*rLen + 4);
	for (int i = 0; i < rLen; i++)
		f.put(r1[i]);	
}
