// Cohen Adair, CS222
// 25 March 2014
// Header file for the Tree class.

#ifndef _TREE_
#define _TREE_

#include <string>
#include "TreeNode.h"
using namespace std;

class TreeNode;

class Tree {

private:
	TreeNode *root;

public:
	Tree();
	~Tree();

	TreeNode *getRoot();
	void setRoot(TreeNode *newRoot);

	void add(string key, string data);
	void remove(string key);
	void print();
	string lookup(string key);
	string next(string key);
	string prev(string key);
	string first();
	string last();
};

#endif
