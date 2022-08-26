#ifndef _BORROW_H_
#define _BORROW_H_
#include "borroworreturn.h"

//Borrow class: children of BorrowOrReturn class
class Borrow : public BorrowOrReturn
{
    //print full command
    friend ostream& operator<<(ostream&, const Borrow&);

public:
    //constructor
    Borrow();

    //decstructor
    ~Borrow();

    //process
    bool processBorrow(Database&, CustomerDatabase&);

private:
    virtual ostream& out(ostream&) const override;
};
#endif