#include "return.h"

//constructor
Return::Return(){}

//destructor
Return::~Return(){}

//processReturn: process the return command
bool Return::processReturn(Database& Datab, CustomerDatabase& cusDatab)
{
	Customer* cusRetriever;

	//check if customer exist
	if (cusDatab.retrieveCustomer(this->getCustomerID(), cusRetriever))
	{
		//check if command contain media
		if (this->media != nullptr) 
		{
			//check if media exist
			InventoryDatabase* meRetriever = nullptr;
			if (Datab.retrieve(*this->media, meRetriever)) 
			{
				//customer return media
				if (cusRetriever->returnMedia(this->media)) 
				{
					//delete command media
					delete this->media;
					this->media = nullptr;

					//add 1 to the stock
					meRetriever->addStock(1);

					//add to the customer history
					cusRetriever->addHistory(this);
					return true;
				}
			}

			//media doesn't exist
			else
				cerr << "Command, media is not in the Database:" << '\n' << "  " << this->fullCommand << endl;
		}

		// command doesn't contain media
		else
			cerr << "Command, this command doesn't contain media:" << '\n' << "  " << this->fullCommand << endl;
	}

	//customer doesn't exist
	else
		cerr << "Command, customer does not exist:" << '\n' << "  " << this->fullCommand << endl;

	//fail to return
	return false;
}

//out: use to set ostream data
ostream& Return::out(ostream& out) const 
{
	out << this->fullCommand;
	return out;
}

// operator<<: use to print command return data
ostream& operator<<(ostream& stream, const Return& r) 
{
	r.out(stream);
	return stream;
}