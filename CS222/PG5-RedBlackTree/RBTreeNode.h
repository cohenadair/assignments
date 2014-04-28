// Cohen Adair, CS222
// 13 April 2014
// Header file for the RBTreeNode class.

#ifndef _RBTreeNode_
#define _RBTreeNode_

#include <string>
#include <fstream>
#include "RBTree.h"
using namespace std;

const string NODE_BLACK = "b";
const string NODE_RED = "r";

class RBTree;

class RBTreeNode {

private:
	string key, data, color;
	RBTreeNode *left;
	RBTreeNode *right;
	RBTreeNode *parent;
	RBTree *t;

	RBTreeNode *getAlphaNext();
	void replace(RBTreeNode *newNode, RBTreeNode *p, RBTreeNode *x);

public:
	RBTreeNode(string newKey, string newData, string newColor, RBTreeNode *newLeft, RBTreeNode *newRight, RBTreeNode *newParent, RBTree *newTree);
	~RBTreeNode();
	
	// getters
	string getKey();
	string getData();
	string getColor();
	RBTreeNode *getLeft();
	RBTreeNode *getRight();
	RBTreeNode *getParent();
	RBTree *getTree();
	
	// setters
	void setColor(string newColor);
	void setLeft(RBTreeNode *newNode);
	void setRight(RBTreeNode *newNode);
	void setParent(RBTreeNode *newNode);
	
	// methods
	void add(string newKey, string newData);
	void remove(string k);
	void rotate(int numberOfRotations);
	bool isDirect();
	string lookup(string k);
	string next(string k);
	string prev(string k);
	string first();
	string last();
	RBTreeNode *getSibling();
	RBTreeNode *getDirect();
	RBTreeNode *getZigzag();
};

#endif
