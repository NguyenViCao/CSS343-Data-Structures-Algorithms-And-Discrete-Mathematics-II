#include "movieclassic.h"

//constructor
MovieClassic::MovieClassic() 
{
    this->movieType = MovieType::ClassicType;
    this->stock = kDEFAULT_STOCK;
    this->title = kDEFAULT_TITLE;
    this->director = kDEFAULT_PERSON;
    this->majorActorFirst = kDEFAULT_PERSON;
    this->majorActorLast = kDEFAULT_PERSON;
    this->month = kDEFAULT_NUM;
    this->year = kDEFAULT_NUM;
}

//copy constructor
MovieClassic::MovieClassic(const MovieClassic& other) 
{
    this->movieType = other.movieType;
    this->stock = other.stock;
    this->title = other.title;
    this->director = other.director;
    this->majorActorFirst = other.majorActorFirst;
    this->majorActorLast = other.majorActorLast;
    this->month = other.month;
    this->year = other.year;
}

//destructor
MovieClassic::~MovieClassic() {}

//setData: read and store the movie to the system
bool MovieClassic::setData(ifstream& stream) 
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

    //set major actor
    stream.ignore();
    stream >> this->majorActorFirst;
    stream.ignore();
    stream >> this->majorActorLast;

    //set month
    stream.ignore();
    stream >> this->month;

    // set year
    stream.ignore();
    stream >> this->year;

    // end of line
    return true;
}

//getMajorActorFirst: return the major actor first name
string MovieClassic::getMajorActorFirst() const
{
    return this->majorActorFirst;
}

//setMajorActorFirst: set the major actor first name for the movie
void MovieClassic::setMajorActorFirst(string first)
{
    this->majorActorFirst = first;
}

//getMajorActorLast: return the major actor last name
string MovieClassic::getMajorActorLast() const
{
    return this->majorActorLast;
}

//setMajorActorLast: set the major actor last name for the movie
void MovieClassic::setMajorActorLast(string last) 
{
    this->majorActorLast = last;
}

//getMonth: return the month of the movie
int MovieClassic::getMonth() const 
{
    return this->month;
}

//setMonth: set the month for the movie
void MovieClassic::setMonth(int month) 
{
    this->month = month;
}

//getMovieType: return the movie type
MovieType MovieClassic::getMovieType() const 
{
    return this->movieType;
}

//operator< sort by release date and major actor
bool MovieClassic::operator<(const InventoryDatabase& other) const 
{
    if (this->getYear() != dynamic_cast<const MovieClassic&>(other).getYear())
        return this->getYear() < dynamic_cast<const MovieClassic&>(other).getYear();

    if (this->getMonth() != dynamic_cast<const MovieClassic&>(other).getMonth())
        return this->getMonth() < dynamic_cast<const MovieClassic&>(other).getMonth();

    return this->getMajorActorFirst().compare(dynamic_cast<const MovieClassic&>(other).getMajorActorFirst()) < 0;
}

//operator<= arithmetic operator, sort by release date and major actor
bool MovieClassic::operator<=(const InventoryDatabase& other) const 
{
    if (this->getYear() > dynamic_cast<const MovieClassic&>(other).getYear())
        return false;

    if (this->getMonth() > dynamic_cast<const MovieClassic&>(other).getMonth())
        return false;

    return this->getMajorActorFirst().compare(dynamic_cast<const MovieClassic&>(other).getMajorActorFirst()) <= 0;
}

//operator> arithmetic operator, sort by release date and major actor
bool MovieClassic::operator>(const InventoryDatabase& other) const 
{
    if (this->getYear() != dynamic_cast<const MovieClassic&>(other).getYear())
        return this->getYear() > dynamic_cast<const MovieClassic&>(other).getYear();

    if (this->getMonth() != dynamic_cast<const MovieClassic&>(other).getMonth())
        return this->getMonth() > dynamic_cast<const MovieClassic&>(other).getMonth();

    return this->getMajorActorFirst().compare(dynamic_cast<const MovieClassic&>(other).getMajorActorFirst()) > 0;
}

//operator>= arithmetic operator, sort by release date and major actor
bool MovieClassic::operator>=(const InventoryDatabase& other) const 
{
    if (this->getYear() < dynamic_cast<const MovieClassic&>(other).getYear())
        return false;

    if (this->getMonth() < dynamic_cast<const MovieClassic&>(other).getMonth())
        return false;

    return this->getMajorActorFirst().compare(dynamic_cast<const MovieClassic&>(other).getMajorActorFirst()) >= 0;
}

//operator== arithmetic operator, sort by release date and major actor
bool MovieClassic::operator==(const InventoryDatabase& other) const 
{
    const MovieClassic& ptrClassic = dynamic_cast<const MovieClassic&>(other);
    return (this->getYear() == dynamic_cast<const MovieClassic&>(other).getYear())&& (this->getMonth() == dynamic_cast<const MovieClassic&>(other).getMonth()
            && (this->getMajorActorFirst().compare(dynamic_cast<const MovieClassic&>(other).getMajorActorFirst()) == 0));
}

// operator= movie assign operator
InventoryDatabase& MovieClassic::operator=(const InventoryDatabase& other)
{
    this->movieType = dynamic_cast<const MovieClassic&>(other).getMovieType();
    this->stock = dynamic_cast<const MovieClassic&>(other).getStock();
    this->director = dynamic_cast<const MovieClassic&>(other).getDirector();
    this->title = dynamic_cast<const MovieClassic&>(other).getTitle();
    this->majorActorFirst = dynamic_cast<const MovieClassic&>(other).getMajorActorFirst();
    this->majorActorLast = dynamic_cast<const MovieClassic&>(other).getMajorActorLast();
    this->month = dynamic_cast<const MovieClassic&>(other).getMonth();
    this->year = dynamic_cast<const MovieClassic&>(other).getYear();
    return *this;
}

// operator!= movie comparison operator
bool MovieClassic::operator!=(const InventoryDatabase& other) const 
{
    return !(*this == dynamic_cast<const MovieClassic&>(other));
}

//print the movie information to the system
void MovieClassic::print(ostream& stream) const 
{
    cout << (char)this->getMovieType() << ", " << this->getStock() << ", " << this->getDirector() << ", "
        << this->getTitle() << ", " << this->getMajorActorFirst() << " " << this->getMajorActorLast() << ", "
        << this->getMonth() << ", " << this->getYear();
}

// operator<< print to the system operator
ostream& operator<<(ostream& out, const MovieClassic& movie) 
{
    movie.print(out);
    return out;
}