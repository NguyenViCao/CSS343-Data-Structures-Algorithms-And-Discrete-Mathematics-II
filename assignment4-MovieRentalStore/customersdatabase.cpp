#include "customersdatabase.h"

//default constructor
CustomerDatabase::CustomerDatabase() {}

//destructor
CustomerDatabase::~CustomerDatabase() {}

//insertCustomer: insert and register the customer to the system
bool CustomerDatabase::insertCustomer(Customer* customer) 
{
	return collection.insert(customer->getId(), customer);
}

//retrieveCustomer: look and retrieve for the customer in the system
bool CustomerDatabase::retrieveCustomer(const int& id, Customer*& retriever) const 
{
	return collection.retrieve(id, retriever);
}

//removeCustomerByID: remove the customer from the system by their ID
bool CustomerDatabase::removeCustomerByID(const int& id)
{
	return collection.remove(id);
}

//getACustomer: find the customer using their ID
const Customer* CustomerDatabase::getACustomer(const int& id) const 
{
	return collection.getValue(id);
}

//display: display a list of customer to the system
void CustomerDatabase::display() const 
{
	collection.display();
}