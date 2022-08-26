#include "borrow.h"

//constructor
Borrow::Borrow(){}

//destructor
Borrow::~Borrow(){}

//processBorrow: check the inventory then process the borrow command
bool Borrow::processBorrow(Database& Datab, CustomerDatabase& cusDatab)
{
	Customer* cusRetriever;

	// check customer exist
	if (cusDatab.retrieveCustomer(this->getCustomerID(), cusRetriever)) 
	{
		//check command if it contains media
		if (this->media != nullptr) 
		{
			//check media exist
			InventoryDatabase* meRetriever = nullptr;
			if (Datab.retrieve(*this->media, meRetriever)) 
			{
				//reduce media strock
				if (meRetriever->reduceStock(1)) 
				{
					//customer borrow media
					cusRetriever->borrowMedia(this->media);
					this->media = nullptr;

					//add customer history
					cusRetriever->addHistory(this);
					return true;
				}

				//else, out of stock
				else
					cerr << "Command, DVD is out of stock:" << '\n' << "  " << this->fullCommand << endl;
			}

			//else, media is not exist
			else 
				cerr << "Command, DVD is not in the store database:" << '\n' << "  " << this->fullCommand << endl;
		}

		//else, command can't operate for this type of media
		else 
			cerr << "Command, this command can't operate for this type of media:" << '\n' << "  " << this->fullCommand << endl;
	}

	//else, customer doesn't exist
	else
		cerr << "Command, customer doesn't exist:" << '\n' << "  " << this->fullCommand << endl;

	//fail tp borrow
	return false;
}

//out: use to set out stream data
ostream& Borrow::out(ostream& out) const 
{
	out << this->fullCommand;
	return out;
}


// operator<<: print command borrow data
ostream& operator<<(ostream& stream, const Borrow& b) 
{
	b.out(stream);
	return stream;
}