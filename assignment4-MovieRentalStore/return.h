#ifndef _RETURN_H_
#define _RETURN_H_
#include "borroworreturn.h"

//Return class: children class of BorrowOrReturn
class Return : public BorrowOrReturn
{
    //print full command
    friend ostream& operator<<(ostream&, const Return&);

public:
    //constructor
    Return();

    //destructor
    ~Return();

    //process
    bool processReturn(Database&, CustomerDatabase&);

private:
    virtual ostream& out(ostream&) const override;
};
#endif