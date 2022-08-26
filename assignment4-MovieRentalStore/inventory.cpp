#include "inventory.h"

// constructor
Inventory::Inventory() 
{
    this->commandCase = CommandCase::InventoryCase;
}

//destructor
Inventory::~Inventory() {}

// processInventory
void Inventory::processInventory(Database& Datab) 
{
    cout << "Inventory:" << endl;
    Datab.display();
}

//operator<<: print command inventory data
ostream& operator<<(ostream& stream, const Inventory& command) 
{
    stream << command.commandCase;
    return stream;
}