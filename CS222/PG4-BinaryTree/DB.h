// Cohen Adair, CS222
// 25 March 2014
// Header file for the DB class.

#ifndef _DB_
#define _DB_

#include <string>
#include "Database.h"
#include "Tree.h"
using namespace std;

class Database;
class Tree;

class DB: public Database {

private:
	Tree *T;

public:
	virtual DRT * search (string key);
	virtual DRT * modify (string key, string data);
	DB();
	~DB();
};

#endif
