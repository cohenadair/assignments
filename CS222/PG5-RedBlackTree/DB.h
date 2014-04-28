// Cohen Adair, CS222
// 13 April 2014
// Header file for the DB class.

#ifndef _DB_
#define _DB_

#include <string>
#include <fstream>
#include "Database.h"
#include "RBTree.h"
using namespace std;

class Database;
class RBTree;

class DB: public Database {

private:
	RBTree *T;

public:
	virtual DRT * search (string key);
	virtual DRT * modify (string key, string data);
	DB();
	~DB();
};

#endif
