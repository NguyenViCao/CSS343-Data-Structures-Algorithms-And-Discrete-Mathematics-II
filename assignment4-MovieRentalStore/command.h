#ifndef _COMMAND_H_
#define _COMMAND_H_
#include "customersdatabase.h"
#include "database.h"

//signature character for each command type
enum CommandCase 
{
    BorrowCase = 'B',
    ReturnCase = 'R',
    HistoryCase = 'H',
    InventoryCase = 'I',
    DefaultCommandCase = '!'
};

//Command class:  create command based on customers' request
//                parent class of BorrowOrReturn, History, and Inventory

class Command
{
    //print out command in full
    friend ostream& operator<<(ostream&, const Command&);

public:
    // constructor
    Command();

    //copy constructor
    Command(const Command&);

    //deconstructor
    virtual ~Command();

    //getters
    int getCustomerID() const;
    CommandCase getCommandType() const;

    //setters
    void setCustomerID(int ID);
    void setCommandType(CommandCase);

    //functions
    virtual void process(Database&, CustomerDatabase&);

protected:
    int customerID;
    CommandCase commandCase;
    string fullCommand;
    virtual ostream& out(ostream&) const;
};
#include "borroworreturn.h"
#include "history.h"
#include "inventory.h"
#endif