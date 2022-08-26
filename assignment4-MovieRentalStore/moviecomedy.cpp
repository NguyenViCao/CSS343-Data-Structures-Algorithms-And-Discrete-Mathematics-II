#include "moviecomedy.h"

//constructor MovieComedy()
MovieComedy::MovieComedy()
{
    this->movieType = MovieType::ComedyType;
    this->stock = kDEFAULT_STOCK;
    this->title = kDEFAULT_TITLE;
    this->director = kDEFAULT_PERSON;
    this->year = kDEFAULT_NUM;
}

//copy constructor MovieComedy
MovieComedy::MovieComedy(const MovieComedy& other)
{
    this->movieType = other.movieType;
    this->stock = other.stock;
    this->title = other.title;
    this->director = other.director;
    this->year = other.year;
}

//destructor
MovieComedy::~MovieComedy(){}

//getMovieType: getter to return the movie type
MovieType MovieComedy::getMovieType() const
{
    return this->movieType;
}

//setData: read and set the movie according to the input file
bool MovieComedy::setData(ifstream& stream)
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
void MovieComedy::print(ostream& stream) const
{
    cout << (char)this->getMovieType() << ", "<< this->getStock() << ", "
        << this->getDirector() << ", "<< this->getTitle() << ", "<< this->getYear();
}

//operator to compare movies
bool MovieComedy::operator<(const InventoryDatabase& other) const
{
    //compare title
    if (this->getTitle().compare(dynamic_cast<const MovieComedy&>(other).getTitle()) != 0)
        return this->getTitle().compare(dynamic_cast<const MovieComedy&>(other).getTitle()) < 0;

    //compare year
    return this->getYear() < dynamic_cast<const MovieComedy&>(other).getYear();
}

//operator
bool MovieComedy::operator<=(const InventoryDatabase& other) const
{
    //compare title
    if (this->getTitle().compare(dynamic_cast<const MovieComedy&>(other).getTitle()) > 0)
        return false;

    //compare year
    return this->getYear() <= dynamic_cast<const MovieComedy&>(other).getYear();
}

//operator 
bool MovieComedy::operator>(const InventoryDatabase& other) const
{
    //compare title
    if (this->getTitle().compare(dynamic_cast<const MovieComedy&>(other).getTitle()) != 0)
        return this->getTitle().compare(dynamic_cast<const MovieComedy&>(other).getTitle()) > 0;

    //compare year
    return this->getYear() > dynamic_cast<const MovieComedy&>(other).getYear();
}

//operator
bool MovieComedy::operator>=(const InventoryDatabase& other) const
{
    //compare title
    if (this->getTitle().compare(dynamic_cast<const MovieComedy&>(other).getTitle()) < 0)
        return false;

    //compare year
    return this->getYear() >= dynamic_cast<const MovieComedy&>(other).getYear();
}

//operator
bool MovieComedy::operator==(const InventoryDatabase& other) const
{
    return (this->getTitle().compare(dynamic_cast<const MovieComedy&>(other).getTitle()) == 0)
        && (this->getYear() == dynamic_cast<const MovieComedy&>(other).getYear());
}

//operator
bool MovieComedy::operator!=(const InventoryDatabase& other) const
{
    return !(*this == dynamic_cast<const MovieComedy&>(other));
}

//assign constructor
InventoryDatabase& MovieComedy::operator=(const InventoryDatabase& other)
{
    this->movieType = dynamic_cast<const MovieComedy&>(other).getMovieType();
    this->stock = dynamic_cast<const MovieComedy&>(other).getStock();
    this->director = dynamic_cast<const MovieComedy&>(other).getDirector();
    this->title = dynamic_cast<const MovieComedy&>(other).getTitle();
    this->year = dynamic_cast<const MovieComedy&>(other).getYear();
    return *this;
}

//operator<< print to the system
ostream& operator<<(ostream& stream, const MovieComedy& movie)
{
    movie.print(stream);
    return stream;
}
