#ifndef _INVENTORY_H_
#define _INVENTORY_H_
#include "command.h"

//Inventory class:	show the current state of the inventory
//					children class of command
class Inventory : public Command
{
    //print full command
    friend ostream& operator<<(ostream&, const Inventory&);

public:
    // constructor
    Inventory();

    //destructor
    ~Inventory();

    //show inventory in here
    void processInventory(Database&);
};
#endif