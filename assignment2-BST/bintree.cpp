#include "bintree.h"

//default constructor that create a tree and point the root to a nullptr
BinTree::BinTree()	
{
	root = nullptr;
}

//copy constructor that calls the copy helper method
BinTree::BinTree(const BinTree& rhs)
{
	copyHelper(root, rhs.root);
}

//destrcutor, delete all the nodes by calling makeEmpty method
BinTree::~BinTree()
{
	makeEmpty();
}

//return true if root is pointing to nullptr, otherwise tree is not empty
bool BinTree::isEmpty() const
{
	return root == nullptr;
}

//empty the BST method
void BinTree::makeEmpty()
{
	//if tree is empty, we're good
	if (root == nullptr)
		return;
	//else, delete each node at a time by calling the helper method
	makeEmptyHelper(root);
	//set root to nullptr to prevent memory leak
	root = nullptr;
}

//assign rhs BST equal to the lhs BST
BinTree& BinTree::operator=(const BinTree& rhs)
{
	//if the two roots are not the same then call makeEmpty method to empty the rhs BST
	//call copyHelper method to 
	if (root != rhs.root)
	{
		makeEmpty();
		copyHelper(root, rhs.root);
	}
	return *this;
}

//compare two BST for same value and same structure
bool BinTree::operator==(const BinTree& rhs) const
{
	//check if the two roots address are not the same
	if (root != rhs.root)
	{
		return comparisionHelper(root, rhs.root);
	}
	//else, two roots have the same address
	else
		return true;
}

//return true if the two BST aren't the same
bool BinTree::operator!=(const BinTree& rhs) const
{
	return !(*this == rhs);
}

//first, check if tree is empty then insert the node
//second, if not empty, call insert helper method to do the insert
//smaller node go to the left, bigger node go to the right
//if the node is duplicated then ignore it
//return true if successfully inserted, otherwise, false
bool BinTree::insert(NodeData* data)
{
	//first, check if tree is empty
	if (root == nullptr)
	{
		//set new NodeData, left and right subtree to nullptr
		root = new Node{ data, nullptr, nullptr };
		return true;
	}
	return insertHelper(data, root);
}

//insertHelper method use to insert node if root != nullptr
bool BinTree::insertHelper(NodeData* newNodeData, Node*& curr)
{
	//if current node doesn't have any child
	if (curr == nullptr)
	{
		//create new NodeData, set left and right subtree to nullptr
		curr = new Node{ newNodeData, nullptr, nullptr };
		return true;
	}

	//if NodeData is smaller than the current node
	else if (*newNodeData < *curr->data)
		return insertHelper(newNodeData, curr->left);

	//if NodeData is bigger than the current node
	else if (*newNodeData > * curr->data)
		return insertHelper(newNodeData, curr->right);

	//last case is the duplicate, ignore and return false
	else
		return false;
}

//call the retrieve helper method to find the targeted node 
//make the retriever points to the target
bool BinTree::retrieve(const NodeData& tar, NodeData*& ret) const
{
	//recursively find the target
	return retrieveHelper(root, tar, ret);
}

//retrieveHelper called inside retrieve, if found return true, else false
bool BinTree::retrieveHelper(Node* curr, const NodeData& tar, NodeData*& ret) const
{
	//if not found, return false
	if (curr == nullptr)
	{
		ret = nullptr;
		return false;
	}

	//traverse left side
	if (tar < *curr->data)
		return retrieveHelper(curr->left, tar, ret);

	//traverse right side
	else if (tar > * curr->data)
		return retrieveHelper(curr->right, tar, ret);

	//last case is when target is found
	else
	{
		ret = curr->data;
		return true;
	}
}

//copyHelper method used inside of copy constructor
void BinTree::copyHelper(Node*& lhs, Node* rhs)
{
	if (rhs != nullptr)
	{
		//create a new node, add new NodeData, set left and right subtree to nullptr
		lhs = new Node{ new NodeData(*rhs->data), nullptr, nullptr };
		
		//copy all left subtree
		copyHelper(lhs->left, rhs->left);
		
		//right subtree
		copyHelper(lhs->right, rhs->right);
	}
}

//return the height of the target node by calling the the helper method
int BinTree::getHeight(const NodeData& tar) const
{
	//keep calling the helper method until we reach the leaf and return the height
	return getHeightHelper(root, tar);
}

//get height helper method called inside of getHeight
//use pre-order (NLR) method to find the targeted node
//if found the targeted node, call the findMax method to calculate the height
int BinTree::getHeightHelper(Node* curr, const NodeData& tar) const
{
	//if root is null, can't find the target
	if (curr == nullptr)
		return 0;

	//else if found the target right away
	else if (*curr->data == tar)
		return findMax(curr);

	//else, keep traversing until find the target
	else
	{
		int height;									//parameter to keep the height
		int l = getHeightHelper(curr->left, tar);	//traverse left side and keep the value of max length on the left
		int r = getHeightHelper(curr->right, tar);	//traverse right side and keep the value of max length on the right
		l > r ? height = l : height = r;			//set height equal the max value
		return height;
	}
}

//assign all nodes of the BST to an array
//apply in-order traverse to fill the nodes in the array
//call the bstreeToArrayHelper method
void BinTree::bstreeToArray(NodeData* arr[])
{
	//set index for the array
	int i = -1;

	//call helper method to put nodes in the array
	bstToArrayHelper(root, arr, i);

	//assign nullptr to the last NodeData in the array
	arr[i + 1] = nullptr;

	//clear the empty tree
	root = nullptr;
}

//helper method to assign nodes from BST to an array
void BinTree::bstToArrayHelper(Node* curr, NodeData* arr[], int& i)
{
	//check if current node doesn't have any children
	if (curr != nullptr)
	{
		//go left
		bstToArrayHelper(curr->left, arr, i);

		//assign the curr node to the array
		arr[i++] = curr->data;

		//points curr data pointer to null ptr to prevent memory leak
		curr->data = nullptr;

		//go right
		bstToArrayHelper(curr->right, arr, i);

		//delete the node
		delete curr;
		curr = nullptr;
	}
}

//from a set of elements and put them into a BSTree
//array must be emptied after transfer all of the elements to BST
void BinTree::arrayToBSTree(NodeData* arr[])
{
	makeEmpty();						//clear the BST first

	//find the max index of the array
	int high = 0;
	int low = 0;
	for (int i = 0; i < kMAXSIZE; i++)
	{
		if (arr[i] != nullptr)
			high++;
		else
			arr[i] = nullptr;
	}
	//set the element from array to BST by calling arrayToBSTHelper method
	arrayToBSTHelper(root, arr, low, high - 1);
}

//called by arrayToBSTree to transfer elements from array to the BST
void BinTree::arrayToBSTHelper(Node* curr, NodeData* arr[], int low, int high)
{
	//if array is empty
	if (low > high)
		curr = nullptr;
	//otherwise, keep transfering the elements from the array to BST
	else
	{
		int mid = (low + high) / 2;		//get the mid element from the array which will be the parent node for the BST
		insert(arr[mid]);
		//adding nodes on the left subtree
		arrayToBSTHelper(curr, arr, low, mid - 1);
		//adding nodes on the right subtree
		arrayToBSTHelper(curr, arr, mid + 1, high);
	}
}

//------------------------- displaySideways ---------------------------------
// Displays a binary tree as though you are viewing it from the side;
// hard coded displaying to standard output.
// Preconditions: NONE
// Postconditions: BinTree remains unchanged.
void BinTree::displaySideways() const {
	sideways(root, 0);
}

//called by getHeightHelper method to calculate the max height
int BinTree::findMax(Node* curr) const
{
	//if the node doesn't have any children
	if(curr == nullptr)
		return 0;

	//otherwise, keep adding as traversing through the nodes
	else
	{
		int height;						//parameter to keep the max height
		int l = findMax(curr->left);	//recursively call itself to find the leaf on the left side
		int r = findMax(curr->right);	//recursively call itself to find the leaf on the right side
		l > r ? height = l : height = r;//set max height equal the max value
		return height + 1;
	}
}

//call by makeEmpty method to empty the BST
void BinTree::makeEmptyHelper(Node*& curr)
{
	//delete all the nodes
	if (curr != nullptr)
	{
		makeEmptyHelper(curr->left);				//delete node on the left
		makeEmptyHelper(curr->right);				//delete node on the right
		//delete the node's data
		if (curr->data != nullptr)
		{
			delete curr->data;
			curr->data = nullptr;
		}
		//delete node
		delete curr;
		curr = nullptr;
	}
}

//==opeartor helper to compare two BSTs
bool BinTree::comparisionHelper(Node* lhs, Node* rhs) const
{
	//if the two roots don't have any children, return true
	if (lhs == nullptr && rhs == nullptr)
		return true;
	//if either one has children and the other doesn't, return false
	else if (lhs != nullptr && rhs == nullptr)
		return false;
	else if (lhs == nullptr && rhs != nullptr)
		return false;
	
	//traverse recursively
	else
	{
		//check for same data as well as for structure
		if (*lhs->data == *rhs->data
			&& comparisionHelper(lhs->left, rhs->left)
			&& comparisionHelper(lhs->right, rhs->right))
			return true;
		else
			return false;
	}
}

//print out the BST, apply in-order traverse by calling the in-order helper method
ostream& operator<<(ostream& stream, const BinTree& tree)
{
	tree.inOrderHelper(stream, tree.root);
	cout << endl;
	return stream;
}

//helper method to print out the tree in-order traverse
void BinTree::inOrderHelper(ostream& stream, Node* curr) const
{
	//check if current node has children or not
	if (curr == nullptr)
		return;
	//else, print from left to right subtree
	else
	{
		inOrderHelper(stream, curr->left);
		stream << *curr->data << " ";
		inOrderHelper(stream, curr->right);
	}
}

//---------------------------- Sideways -------------------------------------
// Helper method for displaySideways
// Preconditions: NONE
// Postconditions: BinTree remains unchanged.
void BinTree::sideways(Node* current, int level) const {
	if (current != NULL) {
		level++;
		sideways(current->right, level);

		// indent for readability, 4 spaces per depth level 
		for (int i = level; i >= 0; i--) {
			cout << "    ";
		}

		cout << *current->data << endl;        // display information of object
		sideways(current->left, level);
	}
}