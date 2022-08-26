#ifndef _MOVIECLASSIC_H_
#define	_MOVIECLASSIC_H_
#include "movie.h"

class MovieClassic: public Movie
{
    // operator<<
    friend ostream& operator<<(ostream&, const MovieClassic&);

public:
    //constructor
    MovieClassic();

    //copy constructor
    MovieClassic(const MovieClassic& classic);

    //destructor
    virtual ~MovieClassic();

    //getters
    int getMonth() const;
    string getMajorActorFirst() const;
    string getMajorActorLast() const;
    virtual MovieType getMovieType() const;

    //setter
    void setMonth(int month);
    void setMajorActorFirst(string first);
    void setMajorActorLast(string last);

    //initial data from movie file
    bool setData(ifstream& stream);

    //function
    void print(ostream& stream) const;

    // arithmetic operator, sort by release date and major actor
    virtual bool operator<(const InventoryDatabase&) const;
    virtual bool operator<=(const InventoryDatabase&) const;
    virtual bool operator>(const InventoryDatabase&) const;
    virtual bool operator>=(const InventoryDatabase&) const;
    virtual bool operator==(const InventoryDatabase&) const;
    virtual bool operator!=(const InventoryDatabase&) const;
    virtual InventoryDatabase& operator=(const InventoryDatabase&);

private:
    string majorActorFirst;
    string majorActorLast;
    int month;
};
#endif