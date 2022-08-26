#ifndef _BST_H_
#define _BST_H_
#include <iostream>
#include <assert.h>

/*
Binary Search Tree class:
 - ADT is used to store movies
 - This is a normal bst with each node has at most two children.
 - Left child is smaller and right child is bigger than the parent
*/

template <typename T>
class BST
{
public:
    //constructor
    BST();

    //destructor
    ~BST();

    //insert object into the tree
    bool insert(T*);

    //retrieve object
    bool retrieve(const T&, T*&) const;

    //displays the nodes of a tree
    void display() const;

    //remove a node
    bool remove(const T&);

    //clear the current tree, deallocates all memory
    void clear();

    // returns true if tree is empty
    bool isEmpty() const;

    // return total node
    int getTotalNode() const;

private:
    //the same as nodedata for previous assignment
    struct Node 
    {
        T* data;
        Node* right;
        Node* left;
    };

    // root of the tree
    Node* root;

    // total nodes
    int totalNode;

    //traverse recursively through the tree, then add node
    //first parameter is new node, second is for traversing
    bool insertHelper(T*, Node*&);

    //traversing recursively through the tree, then retrieve the node
    //first parameter is root, second is for target, third parameter is pointer point to target
    bool retrieveHelper(Node*, const T&, T*&) const;

    //traverse recursively throught the tree, then print the data
    void displayHelper(Node*) const;

    //traversing recursively through the tree, find the node, then delete it
    //first parameter is root, second is the target
    bool removeHelper(Node*& current, const T& key);

    //delete recursively through the tree
    void clearHelper(Node*&);
};

//constructor: set the root
template<typename T>
BST<T>::BST()
{
    root = nullptr;
    totalNode = 0;
}

//destructor: call clear helper method to delete every node
template<typename T>
BST<T>::~BST()
{
    clear();
}

/*insert:   call insertHelper to traverse recursively through the tree 
            insert to the left or right subtree
            if there is any repetition than return false
*/
template<typename T>
bool BST<T>::insert(T* newNode) 
{
    //if tree is empty
    if (root == nullptr) 
    {
        //create a new root, and assign left and right subtree null pointer
        root = new Node{ newNode, nullptr, nullptr };
        assert(root != nullptr); // out of memory
        totalNode++;
        return true;
    }
    //else tree already has root
    else 
    {
        if (insertHelper(newNode, root))
        {
            totalNode++;
            return true;
        }
        return false;
    }
}

/*insertHelper
 - traverse recursively the tree and add the node
 - first parameter is new node, second is for traversing
 */
 template<typename T>
bool BST<T>::insertHelper(T* newNode, Node*& current)
{
    //base case where no root node
    if (current == nullptr) 
    {
        current = new Node{ newNode, nullptr, nullptr };
        assert(current != nullptr); // out of memory
        return true;
    }

    //traverese left if data is smaller than the current data
    else if (*newNode < *current->data)
    {
        return insertHelper(newNode, current->left);
    }

    //traverse right if data is bigger than the current data
    else if (*newNode > *current->data) 
    {
        return insertHelper(newNode, current->right);
    }

    //return false if it is duplicate
    else 
    {
        return false;
    }
}

/*retrieve
 -  find the target and return
 - call the retrieveHelper to traverse recursively
 - return true if retrieve successfully
 - return false if target is not in tree
*/
template<typename T>
bool BST<T>::retrieve(const T& target, T*& retriever) const 
{
    //find the target by traversing recursively
    return retrieveHelper(root, target, retriever);
}

/* retrieveHelper
 - recursively traverse through the tree
 - return true if found the target, false if not found the target
*/
template<typename T>
bool BST<T>::retrieveHelper(Node* current, const T& target, T*& retriever) const 
{
    //base case if target is not found
    if (current == nullptr) 
    {
        retriever = nullptr;
        return false;
    }

    //travere left if the target is < current data
    if (target < *current->data) 
    {
        return retrieveHelper(current->left, target, retriever);
    }

    //traverse right if the target is > current data
    else if (target > *current->data) 
    {
        return retrieveHelper(current->right, target, retriever);
    }

    //target is found
    else 
    {
        retriever = current->data;
        return true;
    }
}

/*remove
 - find the target node and delete it
 - call the removeHelper to traverse recursively
 - return true if remove successfully, false if not removed
*/
template<typename T>
bool BST<T>::remove(const T& target) 
{
    //base case if the root is nullptr, return false
    if (this->root == nullptr) 
    {
        return false;
    }

    //else call removeHelper to traverse recursively
    else 
    {
        if (removeHelper(root, target)) 
        {
            totalNode--;
            return true;
        }
        return false;
    }
}

/* removeHelper
 - recursively traverse the tree
 - this function is sub-function of remove
 - return true if delete the target false if not delete the target
*/
template<typename T>
bool BST<T>::removeHelper(Node*& current, const T& target) 
{
    //base case where root is empty
    if (current == nullptr) 
    {
        return false;
    }

    //travere left tree
    if (target < *current->data) 
    {
        return removeHelper(current->left, target);
    }

    //traverse right tree
    else if (target > * current->data) 
    {
        return removeHelper(current->right, target);
    }

    //else target is found
    else 
    {
        //case 1: the node has no child
        if (current->left == nullptr && current->right == nullptr) 
        {
            delete current->data;
            delete current;
            current = nullptr;
            return true;
        }

        //case 2: the node has two children
        else if (current->left && current->right) 
        {
            //traverse to the smallest child on the right to replace the removed node
            Node* temp = current->right;
            while (temp->left != nullptr) 
            {
                temp = temp->left;
            }
            *current->data = *temp->data;
            return removeHelper(current->right, *temp->data);
        }

        //case 3: the node has one child
        else 
        {
            //check whether the node has left or right child
            Node* child = (current->left) ? current->left : current->right;
            Node* temp = current;
            current = child;
            delete temp->data;
            delete temp;
            temp = nullptr;
            return true;
        }
    }
}

/* display
 - display the node of tree from left to right
 - call the displayHelper traverse recursively
*/
template<typename T>
void BST<T>::display() const 
{
    //call displayHelper to do the work
    displayHelper(root);
}

/* displayHelper
 - traverse recursively through the tree from left to right
*/
template<typename T>
void BST<T>::displayHelper(Node* current) const 
{
    //base case where root is nullptr
    if (current == nullptr)
        return;

    //else print from left to right subtree
    else 
    {
        displayHelper(current->left);
        std::cout << "  " << *current->data << std::endl;
        displayHelper(current->right);
    }
}

/* clear
 - delete every node from the tree
 - this function also will be called when deconstructor is called
*/
template<typename T>
void BST<T>::clear() 
{
    //exit if root is nullptr
    if (root == nullptr)
        return;

    //else tree is not empty, call clearHelper to delete every nodes
    clearHelper(root);

    //set root to nullptr
    root = nullptr;
}

/* clearHelper
 - traverse recursively the tree and delete very nodes
*/
template<typename T>
void BST<T>::clearHelper(Node*& current) 
{
    //if current is not nullptr then delete every nodes
    if (current != nullptr) 
    {
        clearHelper(current->left);         //clear left-subtree
        clearHelper(current->right);        //clear right-subtree
        if (current->data != nullptr) 
        {
            delete current->data;           //delete node data
        }
        delete current;                     //delete node
    }
}

/* isEmpty
 - check tree is empty or not
*/
template<typename T>
bool BST<T>::isEmpty() const 
{
    return root == nullptr;
}

/*getTotalNode
 - return the total number of nodes
*/
template<typename T>
int BST<T>::getTotalNode() const 
{
    return totalNode;
}
#endif