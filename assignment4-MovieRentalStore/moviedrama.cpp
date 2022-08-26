#include "moviedrama.h"

//constructor MovieDrama()
MovieDrama::MovieDrama()
{
    this->movieType = MovieType::DramaType;
    this->stock = kDEFAULT_STOCK;
    this->title = kDEFAULT_TITLE;
    this->director = kDEFAULT_PERSON;
    this->year = kDEFAULT_NUM;
}

//copy constructor MovieDrama
MovieDrama::MovieDrama(const MovieDrama& other)
{
    this->movieType = other.movieType;
    this->stock = other.stock;
    this->title = other.title;
    this->director = other.director;
    this->year = other.year;
}

//destructor
MovieDrama::~MovieDrama() {}

//getMovieType: getter to return the movie type
MovieType MovieDrama::getMovieType() const
{
    return this->movieType;
}

//setData: read and set the movie according to the input file
bool MovieDrama::setData(ifstream& stream)
{
    //set stock
    stream.ignore();
    stream >> this->stock;

    //set director
    stream.ignore();
    getline(stream >> ws, this->director, ',');

    //set title
    stream.ignore();
    getline(stream >> ws, this->title, ',');

    //set year
    stream.ignore();
    string toYear;
    getline(stream >> ws, toYear, '\n');
    stringstream ss;
    ss << toYear;
    ss >> this->year;
    return true;
}

//print method
void MovieDrama::print(ostream& stream) const
{
    cout << (char)this->getMovieType() << ", " << this->getStock() << ", "
        << this->getDirector() << ", " << this->getTitle() << ", " << this->getYear();
}

//operator to compare movies
bool MovieDrama::operator<(const InventoryDatabase& other) const
{
    //compare director
    if (this->getDirector().compare(dynamic_cast<const MovieDrama&>(other).getDirector()) != 0)
        return this->getDirector().compare(dynamic_cast<const MovieDrama&>(other).getDirector()) < 0;

    //compare title
    if (this->getTitle().compare(dynamic_cast<const MovieDrama&>(other).getTitle()) != 0)
        return this->getTitle().compare(dynamic_cast<const MovieDrama&>(other).getTitle()) < 0;

    //return false when greater
    return false;
}

//operator
bool MovieDrama::operator<=(const InventoryDatabase& other) const
{
    //compare director
    if (this->getDirector().compare(dynamic_cast<const MovieDrama&>(other).getDirector()) > 0)
        return false;

    //compare title
    if (this->getTitle().compare(dynamic_cast<const MovieDrama&>(other).getTitle()) > 0)
        return false;

    //return true when less than or equal
    return true;
}

//operator 
bool MovieDrama::operator>(const InventoryDatabase& other) const
{
    //compare director
    if (this->getDirector().compare(dynamic_cast<const MovieDrama&>(other).getDirector()) != 0)
        return this->getDirector().compare(dynamic_cast<const MovieDrama&>(other).getDirector()) > 0;

    //compare title
    if (this->getTitle().compare(dynamic_cast<const MovieDrama&>(other).getTitle()) != 0)
        return this->getTitle().compare(dynamic_cast<const MovieDrama&>(other).getTitle()) > 0;

    // return false when greater
    return false;
}

//operator
bool MovieDrama::operator>=(const InventoryDatabase& other) const
{
    //director first
    if (this->getDirector().compare(dynamic_cast<const MovieDrama&>(other).getDirector()) < 0)
        return false;

    //compare title
    if (this->getTitle().compare(dynamic_cast<const MovieDrama&>(other).getTitle()) < 0)
        return false;

    // return true when less than or equal
    return true;
}

//operator
bool MovieDrama::operator==(const InventoryDatabase& other) const
{
    if ((this->getDirector().compare(dynamic_cast<const MovieDrama&>(other).getDirector()) == 0)
        && (this->getTitle().compare(dynamic_cast<const MovieDrama&>(other).getTitle()) == 0)
        && (this->getYear() == dynamic_cast<const MovieDrama&>(other).getYear()))
        return true;
    return false;
}

//operator
bool MovieDrama::operator!=(const InventoryDatabase& other) const
{
    return !(*this == dynamic_cast<const MovieDrama&>(other));
}

//assign constructor
InventoryDatabase& MovieDrama::operator=(const InventoryDatabase& other)
{
    this->movieType = dynamic_cast<const MovieDrama&>(other).getMovieType();
    this->stock = dynamic_cast<const MovieDrama&>(other).getStock();
    this->director = dynamic_cast<const MovieDrama&>(other).getDirector();
    this->title = dynamic_cast<const MovieDrama&>(other).getTitle();
    this->year = dynamic_cast<const MovieDrama&>(other).getYear();
    return *this;
}

//operator<< print to the system
ostream& operator<<(ostream& stream, const MovieDrama& movie)
{
    movie.print(stream);
    return stream;
}
