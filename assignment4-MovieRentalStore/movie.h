#ifndef _MOVIE_H_
#define _MOVIE_H_
#include "inventorydatabase.h"

/*
Movie class:	this class is used to control the movie object; 
				parent class of Comedy, Drama, and Classic Movie 
*/
class Movie: public InventoryDatabase
{
	//ostream
	friend ostream& operator<<(ostream& stream, const Movie& Movie);

public:
	//destructor
	virtual ~Movie();

	//getters
	virtual string getDirector() const;
	virtual string getTitle() const;
	virtual int getYear() const;

	//setters
	virtual void setDirector(string director);
	virtual void setTitle(string title);
	virtual void setYear(int year);
	virtual bool setData(ifstream& stream) = 0;

	//pure virtual function
	virtual MovieType getMovieType() const = 0;
	virtual MediaType getMediaType() const;

	//operators
	virtual bool operator<(const InventoryDatabase&) const = 0;
	virtual bool operator<=(const InventoryDatabase&) const = 0;
	virtual bool operator>(const InventoryDatabase&) const = 0;
	virtual bool operator>=(const InventoryDatabase&) const = 0;
	virtual bool operator==(const InventoryDatabase&) const = 0;
	virtual bool operator!=(const InventoryDatabase&) const = 0;
	virtual InventoryDatabase& operator=(const InventoryDatabase&) = 0;

protected:
	MovieType movieType;
	string director;
	string title;
	int year;
	virtual void print(ostream& stream) const = 0;
};
#include "moviecomedy.h"
#include "moviedrama.h"
#include "movieclassic.h"
#endif