#ifndef _MOVIECOMEDY_H_
#define _MOVIECOMEDY_H_
#include "movie.h"

/*
MovieComedy class: creates a comedy type of movie
*/
class MovieComedy : public Movie
{
    friend ostream& operator<<(ostream&, const MovieComedy&);

public:
    //constructor
    MovieComedy();

    //copy constructor
    MovieComedy(const MovieComedy& other);

    //destructor
    virtual ~MovieComedy();

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