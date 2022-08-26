#ifndef _INVENTORYDATABASE_H_
#define _INVENTORYDATABASE_H_
#include <iostream>
#include <string>
#include <fstream>
#include <ostream>
#include <sstream>

using namespace std;

const int kDEFAULT_STOCK = 0;
const string kDEFAULT_TITLE = "DEFAULT";
const string kDEFAULT_PERSON = "DEFAULT";
const int kDEFAULT_NUM = 0;

namespace Types 
{
    enum MovieType : char
    {
        ComedyType = 'F',
        ClassicType = 'C',
        DramaType = 'D',
        DefaultMovieType = '!'
    };

    enum MediaType : char 
    {
        DVDMovie = 'D',
        DefaultMediaType = '!'
    };
}
using namespace Types;

class InventoryDatabase
{
    //opertor
    friend ostream& operator<<(ostream& stream, const InventoryDatabase& inven);

public:

    //deconstructor
    virtual ~InventoryDatabase();

    //getter
    virtual int getStock() const;

    //setters
    virtual void setStock(unsigned int amount);
    virtual bool setData(ifstream& stream) = 0;

    //functions
    virtual void addStock(unsigned int amount);
    virtual bool reduceStock(int amount);

    //pure virtual function
    virtual MediaType getMediaType() const = 0;

    // arithmetic operator    
    virtual bool operator<(const InventoryDatabase&) const = 0;
    virtual bool operator<=(const InventoryDatabase&) const = 0;
    virtual bool operator>(const InventoryDatabase&) const = 0;
    virtual bool operator>=(const InventoryDatabase&) const = 0;
    virtual bool operator==(const InventoryDatabase&) const = 0;
    virtual bool operator!=(const InventoryDatabase&) const = 0;
    virtual InventoryDatabase& operator=(const InventoryDatabase&) = 0;

protected:
    int stock;
    MediaType mediaType;

    //sub-function of operator<<
    virtual void print(ostream& stream) const = 0;
};
#include "movie.h"
#endif