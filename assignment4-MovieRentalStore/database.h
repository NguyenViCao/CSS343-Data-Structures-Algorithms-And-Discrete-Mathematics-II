#ifndef _DATABASE_H_
#define _DATABASE_H_
#include <iostream>
#include <map>
#include "bst.h"
#include "inventorydatabase.h"

using namespace std;

/*
Database class: this class is used to control and modify the media in InventoryDatabase
*/

class Database
{
public:
    //constructor
    Database();

    //deconstructor
    ~Database();

    //functions
    bool insert(InventoryDatabase* media);
    bool retrieve(const InventoryDatabase& target, InventoryDatabase*& retriever);
    bool remove(const InventoryDatabase& target);
    void display() const;

    //get total media
    int getTotalMedia() const;
    //helper method for getTotalMedia since media only has movie at the moment
    int getTotalMovie() const;

private:
    //store the inventory for the three types of movie
    map<MovieType, BST<InventoryDatabase>> movies;
    BST<InventoryDatabase> comedies;
    BST<InventoryDatabase> dramas;
    BST<InventoryDatabase> classics;

    //we can further add more media type in the database

    //helper functions
    bool insertMovie(InventoryDatabase* movie);
    bool retrieveMovie(const InventoryDatabase& target, InventoryDatabase*& retriever);
    bool removeMovie(const InventoryDatabase& target);
};
#endif