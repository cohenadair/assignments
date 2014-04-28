// Cohen Adair, CS222
// 24 March 2013
// Method file for the Tree class.

#include <string>
#include "Tree.h"
using namespace std;

Tree::Tree() {
	root = NULL;
}

Tree::~Tree() {
	delete root;
}

TreeNode *Tree::getRoot() {
	return root;
}

void Tree::setRoot(TreeNode *newRoot) {
	root = newRoot;
}

// adds a node with the given key and data to the tree
void Tree::add(string key, string data) {
	if (!root)
		root = new TreeNode(key, data, NULL, NULL, NULL, this);
	else
		root->add(key, data);
}

// removes the node with the given key from the tree
void Tree::remove(string key) {
	if (root)
		root->remove(key);
}

// prints the tree in alphabetical order
void Tree::print() {
	if (root) 
		root->print();
}

// returns the alphabetically next node to the key, "k"
string Tree::lookup(string key) {
	if (root)
		return root->lookup(key);

	return "";
}

// returns the alphabetically next node to the key, "k"
string Tree::next(string key) {
	if (root)
		return root->next(key);

	return "";
}

// returns the alphabetically previous node to the key, "k"
string Tree::prev(string key) {
	if (root)
		return root->prev(key);

	return "";
}

// returns the alphabetically first node in the tree
string Tree::first() {
	if (root)
		return root->first();

	return "";
}

// returns the alphabetically last node in the tree
string Tree::last() {
	if (root)
		return root->last();

	return "";
}
