#ifndef _MEDIA_H_
#define _MEDIA_H_
#include "moviegenre.h"

/*
Media Class: this class is used to build DVDMovie object and store them in a HashTable
*/
class Media
{
public:
	static InventoryDatabase* buildDVDMovie(ifstream& stream);
};
#endif