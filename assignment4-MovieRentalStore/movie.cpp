#include "movie.h"

//destructor
Movie::~Movie() {}

//getDirector: return the director of the movie
string Movie::getDirector() const 
{
    return this->director;
}

//setDirector: set the director for the movie
void Movie::setDirector(string director) 
{
    this->director = director;
}

//getTitle: return the title of the movie
string Movie::getTitle() const 
{
    return this->title;
}

//setTitle: set the title for the movie
void Movie::setTitle(string title) 
{
    this->title = title;
}

//getYear: return the year of the movie
int Movie::getYear() const 
{
    return this->year;
}

//setYear: Set the year for the movie
void Movie::setYear(int year) 
{
    this->year = year;
}

//getDVD: return the media of the movie
MediaType Movie::getMediaType() const 
{
    return MediaType::DVDMovie;
}

//operator to print out to system
ostream& operator<<(ostream& stream, const Movie& movie) 
{
    movie.print(stream);
    return stream;
}