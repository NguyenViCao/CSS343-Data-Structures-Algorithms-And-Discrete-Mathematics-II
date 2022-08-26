#include "media.h"

//constructor
InventoryDatabase* Media::buildDVDMovie(ifstream& stream)
{
	return MovieGenre::buildMovie(stream);
}
