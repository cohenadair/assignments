// Cohen Adair, CS222
// 24 March 2013
// Method file for the TreeNode class.

#include <iostream>
#include <string>
#include "TreeNode.h"
using namespace std;

TreeNode::TreeNode(string newKey, string newData, TreeNode *newLeft, TreeNode *newRight, TreeNode *newParent, Tree *newTree) {
	key = newKey;
	data = newData;
	left = newLeft;
	right = newRight;
	parent = newParent;
	t = newTree;
}

TreeNode::~TreeNode() {
	key = "";
	data = "";
	delete left;
	delete right;
	delete parent;
}

// getters
string TreeNode::getKey() {	return key; }
string TreeNode::getData() { return data; }
TreeNode * TreeNode::getLeft() { return left; }
TreeNode * TreeNode::getRight() { return right; }
TreeNode * TreeNode::getParent() { return parent; }
Tree * TreeNode::getTree() { return t; }

// setters
void TreeNode::setLeft(TreeNode *newNode) { left = newNode; }
void TreeNode::setRight(TreeNode *newNode) { right = newNode; }
void TreeNode::setParent(TreeNode *newNode) { parent = newNode; }

// helper method for Tree->add()
// adds a new node to the tree; if _key exists, does nothing
void TreeNode::add(string newKey, string newData) {
	if (newKey < key) {
		if (left) left->add(newKey, newData);
		else left = new TreeNode(newKey, newData, NULL, NULL, this, t);
	} else if (newKey > key) {
		if (right) right->add(newKey, newData);
		else right = new TreeNode(newKey, newData, NULL, NULL, this, t);
	}
}

// helper method for Tree->remove()
// removes the node with key, "newKey" from the tree
void TreeNode::remove(string k) {
	if (k < key && left)
		left->remove(k);
	else if (k > key && right)
		right->remove(k);
	else if (k == key) {
		if (right && left) {
			TreeNode *n = getAlphaNext();
			key = n->getKey();
			data = n->getData();
			n->remove(n->getKey());
		} else if (left)
			replace(left);
		else if (right)
			replace(right);
		else
			replace(NULL);
	}
} 

// used as a helper function for TreeNode->remove()
// returns the node's alphabetically next node
TreeNode *TreeNode::getAlphaNext() {
	if (right) {
		TreeNode *res = right;

		while (res->getLeft())
			res = res->getLeft();

		return res;
	}
	
	return NULL;
}

// replaces this node with "newNode" and deletes this
// only called on a node with 0 children or 1 child
void TreeNode::replace(TreeNode *newNode) {	
	if (parent) {
		if (parent->getLeft() && key == parent->getLeft()->getKey())
			parent->setLeft(newNode);
		else
			parent->setRight(newNode);

		if (newNode)
			newNode->setParent(parent);
	} 
	
	// if we're deleting the root node
	else { 
		if (newNode)
			newNode->setParent(NULL);

		t->setRoot(newNode);
	}

	left = NULL;
	right = NULL;
	parent = NULL;
	t = NULL;
	delete this;
}

// helper method for Tree->print()
// prints the tree in alphabetical order
void TreeNode::print() {
	if (left) left->print();
	cout << key << endl;
	if (right) right->print();
}

// returns the data associated with the key "k"
// returns "" if the key doesn't exist
string TreeNode::lookup(string k) {
	if (k < key && left)
		return left->lookup(k);
	else if (k > key && right)
		return right->lookup(k);
	else if (k == key)
		return data;
		
	return "";
}

// returns the next key to the key, "k"
string TreeNode::next(string k) {
	string res = "";

	if (k < key && left)
		res = left->next(k);
	else if (k >= key && right)
		res = right->next(k);

	if (key <= k) return res;
	if (res == "") return key;
	if (key <= res) return key;

	return res;
}

// returns the previous key to the key, "k"
string TreeNode::prev(string k) {
	string res = "";

	if (k < key && left)
		res = left->prev(k);
	else if (k >= key && right)
		res = right->prev(k);

	if (key >= k) return res;
	if (res == "") return key;
	if (key >= res) return key;

	return res;
}

// returns the first key in the tree
string TreeNode::first() {
	if (left)
		return left->first();

	return key;
}

// returns the last key in the tree
string TreeNode::last() {
	if (right)
		return right->last();

	return key;
}
