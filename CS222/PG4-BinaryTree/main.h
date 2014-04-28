// Cohen Adair, CS222
// 25 March 2014
// Header file for the main file.

#ifndef _MAIN_
#define _MAIN_

#include <string>
#include "Database.h"
using namespace std;

int main (int argc, char **argv);
void handlePrint(Database *D);
void handleModify(Database *D, int entryNumber, string file, string priority);
void handleDelete(Database *D, string file);
string getKey(int entryNumber, string priority);

#endif
