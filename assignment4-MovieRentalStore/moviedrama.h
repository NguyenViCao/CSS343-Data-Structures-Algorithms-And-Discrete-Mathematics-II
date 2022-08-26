#ifndef _MOVIEDRAMA_H_
#define	_MOVIEDRAMA_H_
#include "movie.h"

class MovieDrama : public Movie
{
    friend ostream& operator<<(ostream&, const MovieDrama&);

public:
    //constructor
    MovieDrama();

    //copy constructor
    MovieDrama(const MovieDrama& other);

    //destructor
    virtual ~MovieDrama();

    //getter
    virtual MovieType getMovieType() const;

    //setter
    bool setData(ifstream& stream);

    void print(ostream& stream) const;

    // arithmetic operator, sort by title and then year release
    virtual bool operator<(const InventoryDatabase&) const;
    virtual bool operator<=(const InventoryDatabase&) const;
    virtual bool operator>(const InventoryDatabase&) const;
    virtual bool operator>=(const InventoryDatabase&) const;
    virtual bool operator==(const InventoryDatabase&) const;
    virtual bool operator!=(const InventoryDatabase&) const;
    virtual InventoryDatabase& operator=(const InventoryDatabase&);
};
#endif