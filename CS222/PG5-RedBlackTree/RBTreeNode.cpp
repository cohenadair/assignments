// Cohen Adair, CS222
// 13 April 2014
// Method file for the RBTreeNode class.

#include <iostream>
#include <string>
#include "RBTreeNode.h"
using namespace std;

RBTreeNode::RBTreeNode(string newKey, string newData, string newColor, RBTreeNode *newLeft, RBTreeNode *newRight, RBTreeNode *newParent, RBTree *newTree) {
	key = newKey;
	data = newData;
	color = newColor;
	left = newLeft;
	right = newRight;
	parent = newParent;
	t = newTree;
}

RBTreeNode::~RBTreeNode() {
	key = "";
	data = "";
	delete left;
	delete right;
	delete parent;
}

// getters
string RBTreeNode::getKey() { return key; }
string RBTreeNode::getData() { return data; }
string RBTreeNode::getColor() { return color; }
RBTreeNode * RBTreeNode::getLeft() { return left; }
RBTreeNode * RBTreeNode::getRight() { return right; }
RBTreeNode * RBTreeNode::getParent() { return parent; }
RBTree * RBTreeNode::getTree() { return t; }

// setters
void RBTreeNode::setColor(string newColor) { color = newColor; }
void RBTreeNode::setLeft(RBTreeNode *newNode) { left = newNode; }
void RBTreeNode::setRight(RBTreeNode *newNode) { right = newNode; }
void RBTreeNode::setParent(RBTreeNode *newNode) { parent = newNode; }

// returns the color of the node "n"
// returns black if "n" is NULL
string GetColor(RBTreeNode *n) {
	if (!n) return NODE_BLACK;
	else return n->getColor();
}

// rules 3-7 for adding a node to the red black tree
void AddProcess(RBTreeNode *x) {
	if (!x->getParent()) // rule 3
		x->setColor(NODE_BLACK);
	else if (!(x->getParent()->getColor() == NODE_BLACK)) { // rule 4
		RBTreeNode *uncle = x->getParent()->getSibling();

		if (uncle && (uncle->getColor() == NODE_RED)) { // rule 5
			uncle->setColor(NODE_BLACK);
			x->getParent()->setColor(NODE_BLACK);
			x->getParent()->getParent()->setColor(NODE_RED);
			x = x->getParent()->getParent();

			AddProcess(x);
		} else if (x->isDirect()) // rule 6
			x->getParent()->rotate(1);
		else
			x->rotate(2); // rule 7
	}
}

// rules 4-10 for deleting a node in the red black tree
void RemoveProcess(RBTreeNode *x, RBTreeNode *p) {
	if (GetColor(x) == NODE_RED) // rule 4
		x->setColor(NODE_BLACK);
	else if (p) { // rule 5
		// rule 6
		RBTreeNode *w = NULL;
		if (x) w = x->getSibling();
		else if (p->getLeft()) w = p->getLeft();
		else w = p->getRight();

		if (GetColor(w) == NODE_RED) { // rule 7
			w->rotate(1);
			RemoveProcess(x, p);
		} else if (w->getLeft() 
			&& w->getRight()
			&& (w->getLeft()->getColor() == NODE_BLACK) 
			&& (w->getLeft()->getColor() == NODE_BLACK)) { // rule 8

			w->setColor(NODE_RED);
			x = p;
			p = p->getParent();
			RemoveProcess(x, p);
		} else if (GetColor(w->getDirect()) == NODE_RED) { // rule 9
			w->getDirect()->setColor(NODE_BLACK);
			w->rotate(1);
		} else { // rule 10
			w->getZigzag()->rotate(2);
			w->setColor(NODE_BLACK);
		}
	} 
}

// helper method for RBTree->add()
// adds a new node to the RBTree; if newKey exists, increments its data by 1
void RBTreeNode::add(string newKey, string newData) {
	RBTreeNode *x = NULL;

	if (newKey < key) {
		if (left) left->add(newKey, newData);
		else x = left = new RBTreeNode(newKey, newData, NODE_RED, NULL, NULL, this, t);
	} else if (newKey > key) {
		if (right) right->add(newKey, newData);
		else x = right = new RBTreeNode(newKey, newData, NODE_RED, NULL, NULL, this, t);
	} else if (newKey == key) {
		data = newData; // override current data	
	}

	if (x) 
		AddProcess(x);
}

// helper method for RBTree->remove()
// removes the node with key, "newKey" from the RBTree
void RBTreeNode::remove(string k) {
	// standard binary tree operations to find and replace (if needed) the node to be removed
	if (k < key && left)
		left->remove(k);
	else if (k > key && right)
		right->remove(k);
	else if (k == key) {
		if (right && left) {
			RBTreeNode *n = getAlphaNext();
			key = n->getKey();
			data = n->getData();
			n->remove(n->getKey());
		} else {
			RBTreeNode *p = NULL, *x = NULL;

			if (left)
				replace(left, p, x);
			else if (right)
				replace(right, p, x);
			else
				replace(NULL, p, x);

			// red-black tree operations 4-7
			if (!(color == NODE_RED))
				RemoveProcess(x, p);

			// physically delete the node
			left = NULL;
			right = NULL;
			parent = NULL;
			t = NULL;
			delete this;
		}
	}
} 

// used as a helper function for RBTreeNode->remove()
// returns the node's alphabetically next node
RBTreeNode *RBTreeNode::getAlphaNext() {
	if (right) {
		RBTreeNode *res = right;

		while (res->getLeft())
			res = res->getLeft();

		return res;
	}
	
	return NULL;
}

// replaces this node with "newNode"
// only called on a node with 0 children or 1 child
void RBTreeNode::replace(RBTreeNode *newNode, RBTreeNode *p, RBTreeNode *x) {	
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

	p = parent;
	if (left) x = left;
	else if (right) x = right;
	else x = NULL;
}

// returns the data associated with the key "k"
// returns "" if the key doesn't exist
string RBTreeNode::lookup(string k) {
	if (k < key && left)
		return left->lookup(k);
	else if (k > key && right)
		return right->lookup(k);
	else if (k == key)
		return data;
		
	return "";
}

// returns the next key to the key, "k"
string RBTreeNode::next(string k) {
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
string RBTreeNode::prev(string k) {
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

// returns the first key in the RBTree
string RBTreeNode::first() {
	if (left)
		return left->first();

	return key;
}

// returns the last key in the RBTree
string RBTreeNode::last() {
	if (right)
		return right->last();

	return key;
}

// returns this node's sibling
RBTreeNode *RBTreeNode::getSibling() {
	if (parent)
		if (parent->getLeft() && parent->getLeft()->getKey() == key) // if this is parent's left
			return parent->getRight();
		else
			return parent->getLeft();

	return NULL;
}

// returns true if this node is the direct child of its parent
bool RBTreeNode::isDirect() {
	RBTreeNode *gp = parent->getParent();

	// if there's no grandparent, this is direct
	if (!gp) 
		return true;

	// if parent and this is a left child, this is direct
	if (gp->getLeft() 
		&& gp->getLeft()->getKey() == parent->getKey() 
		&& parent->getLeft() 
		&& parent->getLeft()->getKey() == key)
		return true;

	// if parent and this is a right child, this is direct
	if (gp->getRight() 
		&& gp->getRight()->getKey() == parent->getKey() 
		&& parent->getRight()
		&& parent->getRight()->getKey() == key)
		return true;

	return false;
}

// returns this node's direct child; returns NULL if this node has no parent
// if this node is its parent's left, returns this node's left
// if this node is its parent's right, returns this node's right 
RBTreeNode *RBTreeNode::getDirect() {
	if (!parent) return NULL;

	if (parent->getLeft() && key == parent->getLeft()->getKey())
		return left;
	else
		return right;
}

// returns this node's zigzag child; returns NULL if this node has no parent
// if this node is its parent's left, returns this node's right
// if this node is its parent's right, returns this node's left 
RBTreeNode *RBTreeNode::getZigzag() {
	if (!parent) return NULL;

	if (key == parent->getLeft()->getKey())
		return right;
	else
		return left;
}

// rotates this node up "numberOfRotations" times
void RBTreeNode::rotate(int numberOfRotations) {
	for (int i = 1; i <= numberOfRotations; i++) {
		RBTreeNode *x = this;
		RBTreeNode *p = parent;
		RBTreeNode *gp = parent->getParent();
		RBTreeNode *z = NULL;

		if (x->getDirect())
			z = x->getDirect()->getSibling();
	
		// 1
		x->setParent(gp);

		// 2
		if (!gp)
			t->setRoot(x);
		else if (gp->getRight() && (gp->getRight()->getKey() == p->getKey()))
			gp->setRight(x);
		else
			gp->setLeft(x);		

		// 3
		p->setParent(x);

		// 4 & 5
		if (p->getLeft() && (p->getLeft()->getKey() == x->getKey())) {
			x->setRight(p);
			p->setLeft(z);
		} else {
			x->setLeft(p);
			p->setRight(z);
		}

		// 6
		if (z)
			z->setParent(p);	
	}
}
