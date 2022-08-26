#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_
#include <string>
#include "bst.h"

using namespace std;

//set constant table size
const int kTABLE_SIZE = 97;

template <typename Key, typename Val>
/*
HashTable class:	this class is used to create a hashtable to store values and their key in an array type structure
					this hashtable is based on probing technique
					this hashtable uses the open method (if values are has the same key then they will join the bucket and form a bst inside that bucket)
*/
class HashTable
{
public:
    //constructor
    HashTable();

    //destructor
    ~HashTable();

    //insert pair
    bool insert(Key key, Val* val);

    //retrieve value by key
    bool retrieve(Key key, Val*& retriever) const;

    //get value by key
    const Val* getValue(Key key) const;

    //remove value by key
    bool remove(Key key);

    //display all the values
    void display() const;

private:
    //bst as each bucket
    BST<Val>* table[kTABLE_SIZE];

    //destructor helper function
    void clear();
};

//IMPLEMENTATION

//constructor
template <typename Key, typename Val>
HashTable<Key, Val>::HashTable() 
{
    //initialize all bucket as nullptr
    for (int i = 0; i < kTABLE_SIZE; i++) 
    {
        this->table[i] = nullptr;
    }
}

//destructor: call makeEmpty helper method
template <typename Key, typename Val>
HashTable<Key, Val>::~HashTable() 
{
    clear();
}

//insert: insert an object which is the value with it corresponding key to the bucket
template <typename Key, typename Val>
bool HashTable<Key, Val>::insert(Key key, Val* val) 
{
    //get hash#
    const int hash = reinterpret_cast<const int&>(key) % kTABLE_SIZE;

    //eliminate negative cases
    if (hash < 0) 
    {
        return false;
    }

    //create a new bst
    if (table[hash] == nullptr) 
    {
        table[hash] = new BST<Val>();
        return table[hash]->insert(val);
    }

    //handle collision
    else 
    {
        //if return false, front end incharge of memory management
        return table[hash]->insert(val);
    }
    return false;
}

//retrieve: return the value of they key from the HashTable
template <typename Key, typename Val>
bool HashTable<Key, Val>::retrieve(Key key, Val*& retriever) const 
{
    //get hash#
    const int hash = reinterpret_cast<const int&>(key) % kTABLE_SIZE;

    //eliminate negative case
    if (hash < 0) 
    {
        return false;
    }

    //if empty bucket, return false
    if (table[hash] == nullptr) 
    {
        return false;
    }

    //else, look for the value
    else 
    {
        Val* tempRetrive = nullptr;
        const Val tempTarget(key);
        return table[hash]->retrieve(tempTarget, retriever);
    }
    return false;
}

//getValue: get the value from the table
template <typename Key, typename Val>
const Val* HashTable<Key, Val>::getValue(Key key) const 
{
    //get hash#
    const int hash = reinterpret_cast<const int&>(key) % kTABLE_SIZE;

    //eliminate negative cases
    if (hash < 0) 
    {
        return nullptr;
    }

    //if the bucket is empty
    if (table[hash] == nullptr) 
    {
        return nullptr;
    }

    //find the bucket at bst root, or traversing through the tree
    else 
    {
        Val* tempRetrive = nullptr;
        const Val tempTarget(key);
        if (table[hash]->retrieve(tempTarget, tempRetrive))
            return tempRetrive;

        return nullptr;
    }
    return nullptr;
}

//remove: delete the value of the key
template <typename Key, typename Val>
bool HashTable<Key, Val>::remove(Key key) 
{
    //get hash#
    const int hash = reinterpret_cast<const int&>(key) % kTABLE_SIZE;

    //eliminate negative cases
    if (hash < 0) 
    {
        return false;
    }

    //if the bucket is empty
    if (table[hash] == nullptr) 
    {
        return false;
    }
    else 
    {
        Val* tempRetrive = nullptr;
        const Val tempTarget(key);
        return table[hash]->remove(tempTarget);
    }
}

//display: display the table
template<typename Key, typename Val>
void HashTable<Key, Val>::display() const 
{
    for (int i = 0; i < kTABLE_SIZE; i++) 
    {
        if (table[i] != nullptr)
            table[i]->display();
    }
}

//clear: destructor method
template <typename Key, typename Val>
void HashTable<Key, Val>::clear() 
{
    //delete the bucket
    for (int i = 0; i < kTABLE_SIZE; i++) 
    {
        //delete the tree
        if (this->table[i] != nullptr) 
        {
            this->table[i]->clear();

            //delete the bucket
            delete this->table[i];
            this->table[i] = nullptr;
        }
    }
}
#endif