#ifndef _BORROWORRETURN_H_
#define _BORROWORRETURN_H_
#include "command.h"

//BorrowOrReturn class: parent of Borrow and Return since they share some common features

class BorrowOrReturn : public Command
{
    //print full command
    friend ostream& operator<<(ostream&, const BorrowOrReturn&);

public:
    //constructor:
    BorrowOrReturn();

    //destructor
    ~BorrowOrReturn();

    //setter
    bool setData(ifstream&);

protected:
    MediaType mediaType;
    MovieType movieType;
    InventoryDatabase* media;

    //functions for setData
    void processComedy(ifstream&, InventoryDatabase*&);
    void processClassic(ifstream&, InventoryDatabase*&);
    void processDrama(ifstream&, InventoryDatabase*&);
    void processError(ifstream&, const string&, const string&);

    // use to set data to ostream
    virtual ostream& out(ostream&) const;
};
#include "borrow.h"
#include "return.h"
#endif