#ifndef BINTREE_H_
#define BINTREE_H_
#include <iostream>
#include "nodedata.h"
using namespace std;

const int kMAXSIZE = 100;					//max size of the array

class BinTree {				// you add class/method comments and assumptions
	friend ostream& operator<<(ostream&, const BinTree&);

public:
	//constructors
	BinTree();								// default constructor
	BinTree(const BinTree&);				// copy constructor
	~BinTree();								// destructor, calls makeEmpty	
	
	bool isEmpty() const;					// true if tree is empty, otherwise false
	void makeEmpty();						// make the tree empty so isEmpty returns true

	//overloading operators
	BinTree& operator=(const BinTree&);	
	bool operator==(const BinTree&) const;
	bool operator!=(const BinTree&) const;
	bool insert(NodeData*);					//insert a node into the tree; return true if successful, false if duplicate or can't insert
	bool retrieve(const NodeData&, NodeData*&) const;
	
	//methods
	int getHeight(const NodeData&)const;	// find the height of a given value in the tree
	void bstreeToArray(NodeData* []);		// fill an array of Nodedata* by using an inorder traversal of the tree
	void arrayToBSTree(NodeData* []);		// function to builds a balanced BinTree from a sorted array of NodeData* leaving the array filled with NULLs
	void displaySideways() const;			// provided below, displays the tree sideways

private:
	struct Node {
		NodeData* data;						// pointer to data object
		Node* left;							// left subtree pointer
		Node* right;						// right subtree pointer
	};
	Node* root;								// root of the tree

// helper functions
	void inOrderHelper(ostream&, Node*)const;	//operator<< func helper
	void sideways(Node*, int) const;			// provided below, helper for displaySideways()
	void copyHelper(Node*&, Node*);				// use in operator= and copy constructor
	bool insertHelper(NodeData*, Node*&);		// insert function helper
	bool retrieveHelper(Node*, const NodeData&, NodeData*&)const;	//retrieve function helper
	int getHeightHelper(Node*, const NodeData&)const;	//find the node and calc the distance from the node to the leaf
	int findMax(Node*)const;					//find node's max height and return its height to getHeight func
	void bstToArrayHelper(Node*, NodeData* [], int&);	//put every nodes of the BinTree to an array
	void arrayToBSTHelper(Node*, NodeData* [], int, int);	//put every elements in the array to the BinTree
	void makeEmptyHelper(Node*&);				// make empty func helper
	bool comparisionHelper(Node*, Node*) const;		//opeartor== func helper
};
#endif