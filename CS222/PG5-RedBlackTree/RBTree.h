// Cohen Adair, CS222
// 13 April 2014
// Header file for the RBTree class.

#ifndef _TREE_
#define _TREE_

#include <string>
#include <fstream>
#include "RBTreeNode.h"
using namespace std;

class RBTreeNode;

class RBTree {

private:
	RBTreeNode *root;

public:
	RBTree();
	~RBTree();

	RBTreeNode *getRoot();
	void setRoot(RBTreeNode *newRoot);

	void add(string key, string data);
	void remove(string key);
	string lookup(string key);
	string next(string key);
	string prev(string key);
	string first();
	string last();
};

#endif
