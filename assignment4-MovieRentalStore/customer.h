#ifndef _CUSTOMER_H_
#define _CUSTOMER_H_
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <list>
#include <algorithm>
#include "inventorydatabase.h"

using namespace std;

//declare constant
const int kMINID = 1;                    //smallest id
const int kMAXID = 9999;                 //max id
const int kDEFAULT_ID = 0;               //default id
const string kDEFAULT_NAME = "DEFAULT";  //default name

//class identifier
class Command;

// Class Customer: This class create a a new list of customers into the system

class Customer 
{
    //display customer information
    friend ostream& operator<<(ostream&, const Customer&);

public:
    //constructors
    Customer();
    Customer(int id);
    Customer(int id, string first, string last);

    //copy constructor
    Customer(const Customer& other);

    //destructor
    ~Customer();

    //getters
    int getId() const;
    string getFirstName() const;
    string getLastName() const;
    // get history borrow or return
    const vector<Command*> getHistories() const;

    //setters
    void setID(int id);
    void setFirstName(string first);
    void setLastName(string last);
    bool setData(ifstream& infile);

    //functions
    void borrowMedia(InventoryDatabase* media);

    // customer has returned media
    bool returnMedia(InventoryDatabase* target);

    // add commands history
    void addHistory(Command* command);

    // operator in case needed
    bool operator<(const Customer&) const;
    bool operator<=(const Customer&) const;
    bool operator>(const Customer&) const;
    bool operator>=(const Customer&) const;
    bool operator==(const Customer&) const;
    bool operator!=(const Customer&) const;

private:
    int id;                                 //customer ID
    string firstName;                       //customer first name
    string lastName;                        //customer last name
    vector<InventoryDatabase*> borrowing;   //customer media borrow currently
    vector<Command*> history;               //customer history borrow or return
};
#endif