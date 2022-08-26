#ifndef _CUSTOMER_DATABASE_H_
#define _CUSTOMER_DATABASE_H_
#include "customer.h"
#include "hashtable.h"

//CustomerDatabase class: This class control and modify the information of customer in the system

class CustomerDatabase
{
public:
    //constructor
    CustomerDatabase();

    //destructor
    ~CustomerDatabase();

    //insert customer
    bool insertCustomer(Customer* customer);

    //retrieve customer
    bool retrieveCustomer(const int& id, Customer*& retriever) const;

    //remove customer by giving the customer's ID
    bool removeCustomerByID(const int& id);

    //return a constant pointer of customer by giving customer ID
    const Customer* getACustomer(const int& id) const;

    // display all customer
    void display() const;

private:
    // a table to hold all customers
    HashTable<int, Customer> collection;
};
#endif