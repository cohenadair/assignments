// Cohen Adair, CS222
// 25 March 2014
// Header file for the TreeNode class.

#ifndef _TREENODE_
#define _TREENODE_

#include <string>
#include "Tree.h"
using namespace std;

class Tree;

class TreeNode {

private:
	string key, data;
	TreeNode *left;
	TreeNode *right;
	TreeNode *parent;
	Tree *t;

	TreeNode *getAlphaNext();
	void replace(TreeNode *newNode);

public:
	TreeNode(string newKey, string newData, TreeNode *newLeft, TreeNode *newRight, TreeNode *newParent, Tree *newTree);
	~TreeNode();
	
	// getters
	string getKey();
	string getData();
	TreeNode *getLeft();
	TreeNode *getRight();
	TreeNode *getParent();
	Tree *getTree();
	
	// setters
	void setLeft(TreeNode *newNode);
	void setRight(TreeNode *newNode);
	void setParent(TreeNode *newNode);
	
	// methods
	void add(string newKey, string newData);
	void remove(string k);
	void print();
	string lookup(string k);
	string next(string k);
	string prev(string k);
	string first();
	string last();
};

#endif
