// Cohen Adair, CS201
// Header file for main.cpp.

#ifndef _MAIN_
#define _MAIN_

#include <string>
using namespace std;

int main (int argc, char **argv);
void shellSort (fstream& f, int rLen, int r);
int getRecordLength(char * A, int n);
string getRecord(fstream& f, int rLen, int r);
void swapRecords(fstream& f, int rLen, int n1, int n2, string r1, string r2);

#endif
