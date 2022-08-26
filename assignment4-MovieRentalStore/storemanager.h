#ifndef _STOREMANAGER_H_
#define _STOREMANAGER_H_
#include <fstream>
#include "customersdatabase.h"
#include "database.h"
#include "media.h"
#include "commandtype.h"
using namespace std;

/*
StoreManager Class:
 - read file from main to initialize customer, movie, commands
 - Process Borrow or Return
 - Display History
 - Display all borrow and return of a customer
 - Display inventory
 - Output all Comedy movies, then all Dramas, then all Classics
*/
class StoreManager 
{
public:
    //constructor
    StoreManager();

    //destructor 
    ~StoreManager();

    //reads customers information from provided text file
    void buildCustomers(ifstream& stream);

    //reads movies information from provided text file
    void buildMovies(ifstream& stream);

    //reads all commands from provided text file
    void processCommands(ifstream& stream);

private:
    //database of customers
    CustomerDatabase customerDatabase;

    //database of dvd movies
    Database database;
};
#endif