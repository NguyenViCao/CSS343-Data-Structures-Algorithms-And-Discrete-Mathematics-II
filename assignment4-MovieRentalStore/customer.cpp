#include "customer.h"
#include "command.h"

//default constructor
Customer::Customer() 
{
	firstName = kDEFAULT_NAME;
	lastName = kDEFAULT_NAME;
	id = kDEFAULT_ID;
}

//constructor with only customer id insert in
Customer::Customer(int id) 
{
	this->id = id;  //set new id
}

//constructor with customer id, last name and first name insert in
Customer::Customer(int id, string lastName, string firstName) 
{
	this->id = id;
	this->firstName = lastName;
	this->lastName = firstName;
}

//copy constructor
Customer::Customer(const Customer& other) 
{
	firstName = other.firstName;
	lastName = other.lastName;
	id = other.id;
}

//destructor
Customer::~Customer() 
{
	//clear borrowing
	for (int i = borrowing.size(); i > 0; i--) 
	{
		if (borrowing.back()) {
			delete borrowing.back();
		}
		borrowing.pop_back();
	}

	//clear history
	for (int i = history.size(); i > 0; i--) 
	{
		if (history.back()) {
			delete history.back();
		}
		history.pop_back();
	}
}

//getID: get and return the ID
int Customer::getId() const 
{
	return id;
}

//getLastName: get and return the last name 
string Customer::getLastName() const 
{
	return lastName;
}

//getFirstName: get and return the first name
string Customer::getFirstName() const 
{
	return firstName;
}

//getHistories: return the history of the customer
const vector<Command*> Customer::getHistories() const 
{
	return history;
}

//setID: modify the customer ID
void Customer::setID(int id) 
{
	this->id = id;
}

//setFirstName: modify the customer first name
void Customer::setFirstName(string first) 
{
	this->firstName = first;
}

//setLastName: modify the customer last name
void Customer::setLastName(string last) 
{
	this->lastName = last;
}

//setData: read and get the customer information from the file
bool Customer::setData(ifstream& stream) 
{
	bool valid = true;

	stream >> id;
	if (stream.fail() || id < kMINID || id > kMAXID) 
	{
		stream.clear();
		char temp;
		while (stream.get(temp) && temp != '\n');
		return false;
	}

	stream >> lastName >> firstName;

	//read until end of statement
	if (!valid) 
	{
		stream.clear();
		char temp;
		while (stream.get(temp) && temp != '\n');
		return false;
	}
	return valid;
}

//borrowMedia: Store the customer request
void Customer::borrowMedia(InventoryDatabase* media) 
{
	borrowing.push_back(media);
}

//returnMedia: return the media from the customer back to the system
bool Customer::returnMedia(InventoryDatabase* target) 
{
	bool isReturn = false;
	for (int i = 0; i < borrowing.size() && isReturn == false; i++) 
	{
		if (*borrowing.at(i) == *target) 
		{
			InventoryDatabase* temp = borrowing.at(i);
			borrowing.at(i) = borrowing.at(borrowing.size() - 1);
			borrowing.at(borrowing.size() - 1) = temp;
			if (borrowing.back()) 
			{
				delete borrowing.back();
			}
			borrowing.pop_back();
			isReturn = true;
		}
	}
	return isReturn;
}

//addHistory: add the customer request into their history
void Customer::addHistory(Command* command) 
{
	history.push_back(command);
}

//operator<: compare customers ID
bool Customer::operator<(const Customer& other) const 
{
	return id < other.id;
}

//operator<=: compare customers ID
bool Customer::operator<=(const Customer& other) const 
{
	return id <= other.id;
}

//operator>: compare customers ID
bool Customer::operator>(const Customer& other) const 
{
	return id > other.id;
}

//operator>=: compare customers ID
bool Customer::operator>=(const Customer& other) const 
{
	return id >= other.id;
}

//operator==: compare customers ID
bool Customer::operator==(const Customer& other) const 
{
	return id == other.id;
}

//operator!=: compare customers ID
bool Customer::operator!=(const Customer& other) const 
{
	return id != other.id;
}

//operator<<: print out the customer ID, last name and first name in order
ostream& operator<<(ostream& out, const Customer& customer) 
{
	out << customer.id
		<< " " << customer.lastName
		<< " " << customer.firstName;
	return out;
}