#include "history.h"

//constructor
History::History() 
{
	this->commandCase = CommandCase::HistoryCase;
	this->customerID = kDEFAULT_ID;
}

//destructor
History::~History(){}

//setData
bool History::setData(ifstream& stream) 
{
	stream.ignore();
	stream >> this->customerID;
	if (stream.fail()) 
	{
		cout << "Customer ID is invalid" << endl;
		stream.clear();
		stream.ignore(99, '\n');
		return false;
	}
	return true;
}

//processHistory: creates the history command 
bool History::processHistory(CustomerDatabase& cusDatab) 
{
	Customer* cusRetriver = nullptr;

	//found customer
	if (cusDatab.retrieveCustomer(this->getCustomerID(), cusRetriver)) 
	{
		//labeling
		cout << "History of " << this->getCustomerID()
			<< " " << cusRetriver->getFirstName()
			<< " " << cusRetriver->getLastName() << ':' << endl;

		//empty
		if (cusRetriver->getHistories().empty()) 
		{
			cout << "  " << "Empty!" << endl;
		}

		//already has history
		else 
		{
			for (int i = 0; i < cusRetriver->getHistories().size(); i++) 
			{
				cout << "  " << *cusRetriver->getHistories().at(i) << endl;
			}
			return true;
		}
	}

	// customer not found
	else 
	{
		cerr << "Command, customer not found to show history:"
			<< '\n' << "  " << this->fullCommand << endl;
	}
	return false;
}

//out: set outsteam data
ostream& History::out(ostream& out) const 
{
	out << (char)this->commandCase << " " << this->getCustomerID();
	return out;
}

//operator<<: print out comman history data
ostream& operator<<(ostream& stream, const History& command) 
{
	command.out(stream);
	return stream;
}