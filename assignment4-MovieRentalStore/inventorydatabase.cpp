#include "inventorydatabase.h"

InventoryDatabase::~InventoryDatabase(){}

//getStock: return the amount of stock in the inventory
int InventoryDatabase::getStock() const
{
	return this->stock;
}

//setStock: set the modified number of stock in the inventory
void InventoryDatabase::setStock(unsigned int amount)
{
	this->stock = amount;
}

//addStock: increase the amount in the inventory
void InventoryDatabase::addStock(unsigned int amount)
{
	this->stock += amount;
}

//reduceStock: reduce the amount in the inventory
bool InventoryDatabase::reduceStock(int amount)
{
	if (this->stock - amount < 0)
		return false;
	else
		this->stock -= amount;
	return true;
}

//operator<< print out the inventory 
ostream& operator<<(ostream& stream, const InventoryDatabase& inven)
{
	inven.print(stream);
	return stream;
}
