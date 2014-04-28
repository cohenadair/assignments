// Cohen Adair, CS222
// 13 April 2014
// Method file for the RBTree class.

#include <string>
#include <iostream>
#include "RBTree.h"
using namespace std;

RBTree::RBTree() {
	root = NULL;
}

RBTree::~RBTree() {
	delete root;
}

RBTreeNode *RBTree::getRoot() {
	return root;
}

void RBTree::setRoot(RBTreeNode *newRoot) {
	root = newRoot;
}

// adds a node with the given key and data to the RBTree
void RBTree::add(string key, string data) {
	if (!root)
		root = new RBTreeNode(key, data, NODE_BLACK, NULL, NULL, NULL, this);
	else
		root->add(key, data);
}

// removes the node with the given key from the RBTree
void RBTree::remove(string key) {
	if (root)
		root->remove(key);
}

// returns the data associated with "key"
string RBTree::lookup(string key) {
	if (root)
		return root->lookup(key);

	return "";
}

// returns the alphabetically next node to the key, "key"
string RBTree::next(string key) {
	if (root)
		return root->next(key);

	return "";
}

// returns the alphabetically previous node to the key, "key"
string RBTree::prev(string key) {
	if (root)
		return root->prev(key);

	return "";
}

// returns the alphabetically first node in the RBTree
string RBTree::first() {
	if (root)
		return root->first();

	return "";
}

// returns the alphabetically last node in the RBTree
string RBTree::last() {
	if (root)
		return root->last();

	return "";
}
