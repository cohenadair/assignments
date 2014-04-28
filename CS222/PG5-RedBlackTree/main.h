// Cohen Adair, CS222
// 13 April 2014
// Header file for the main file.

#ifndef _MAIN_
#define _MAIN_

#include <string>
#include "Database.h"
using namespace std;

int main (int argc, char **argv);
void handlePrint(Database *D, ostream &o);
void handleAdd(Database *D, ostream &o, string bookTitle);
void handleDelete(Database *D, ostream &o,string bookTitle);
void handleCount(Database *D, ostream &o);

#endif
