#include "command.h"

//constructor
Command::Command() 
{
	this->commandCase = DefaultCommandCase;
	this->customerID = kDEFAULT_ID;
	this->fullCommand = DefaultCommandCase;
}

//copy constructor 
Command::Command(const Command& other) 
{
	this->commandCase = other.commandCase;
	this->customerID = other.customerID;
	this->fullCommand = other.fullCommand;
}

//destructor 
Command::~Command() {}

//getCustomerID
int Command::getCustomerID() const 
{
	return this->customerID;
}

//setCustomerID
void Command::setCustomerID(int ID)
{
	this->customerID = ID;
}

//getCommandType
CommandCase Command::getCommandType() const 
{
	return this->commandCase;
}

//setCommandType
void Command::setCommandType(CommandCase in) 
{
	this->commandCase = in;
}

void Command::process(Database& Datab, CustomerDatabase& cusDatab)
{
	//use to check if it is process or not
	bool flag = false;

	//select type of command
	switch (this->commandCase) 
	{
		//borrow
	case BorrowCase:
		flag = dynamic_cast<Borrow*>(this)->processBorrow(Datab, cusDatab);
		break;

		//return
	case ReturnCase:
		flag = dynamic_cast<Return*>(this)->processReturn(Datab, cusDatab);
		break;

		//display history
	case HistoryCase:
		flag = dynamic_cast<History*>(this)->processHistory(cusDatab);
		break;

		//check inventory
	case InventoryCase:
		dynamic_cast<Inventory*>(this)->processInventory(Datab);
		break;

		//default case
	default:
		cerr << "Command, nothing to process" << endl;
		flag = false;
		break;
	}

	// delete this object
	if (!flag|| this->commandCase == HistoryCase || this->commandCase == InventoryCase)
		delete this;
}

//out: use to set ostream data
ostream& Command::out(ostream& out) const 
{
	out << (char)this->commandCase;
	return out;
}

// operator<<: print out the command
ostream& operator<<(ostream& stream, const Command& comm) 
{
	comm.out(stream);
	return stream;
}