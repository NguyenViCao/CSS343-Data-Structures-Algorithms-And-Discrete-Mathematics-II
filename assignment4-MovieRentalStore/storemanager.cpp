#include "storemanager.h"
#include <iostream>

//constructor
StoreManager::StoreManager(){}

//destructor
StoreManager::~StoreManager(){}

//buildCustomers: read data from the provided text file and build a list of customers from that
void StoreManager::buildCustomers(ifstream& stream)
{
    //if file can't be read then display error message 
    if (!stream) 
    {
        cout << "Cannot read customer file!" << endl;
        return;
    }

    Customer* ptr;                                  //used for create new customer
    bool checkData;                                 //used for reading good data
    while (!stream.eof()) 
    {
        ptr = new Customer();                       //create new customer object

        //set data for customer
        if (ptr->setData(stream)) 
        {
            //ignore duplicate
            if (!customerDatabase.insertCustomer(ptr)) 
            {
                delete ptr;
            }
        }

        //else invalid data
        else 
        {
            delete ptr;
        }
    }

    //close files
    stream.close();
}

//buildMovies: read data from the provided text file and build a list of movies
void StoreManager::buildMovies(ifstream& stream)
{
    //if file can't be read then display error message 
    if (!stream) 
    {
        cout << "Cannot read Movies file" << endl;
        return;
    }

    //create, and retrieve movie object    
    InventoryDatabase* obj;
    InventoryDatabase* dup;

    //read file till the last line
    while (!stream.eof()) 
    {
        //create new object in the inventory database
        obj = Media::buildDVDMovie(stream);

        //if object exist
        if (obj != nullptr) {

            //insert, if duplicate add more stock
            if (!database.insert(obj)) 
            {
                if (database.retrieve(*obj, dup)) 
                {
                    dup->addStock(obj->getStock());
                    delete obj;
                }
            }
        }
        obj = dup = nullptr;
    }

    // close file
    stream.close();
}

//processCommands: get customer commands from the file to process
void StoreManager::processCommands(ifstream& stream) 
{
    //if file can't be read then display error message 
    if (!stream) 
    {
        cout << "Cannot read command file" << endl;
        return;
    }

    //create command object
    Command* command;

    //read file till the last line
    while (!stream.eof()) 
    {
        //create command
        command = CommandType::createCommand(stream);

        //process command
        if (command != nullptr) 
        {
            command->process(database, customerDatabase);
            command = nullptr;
        }
    }

    // close file
    stream.close();
}