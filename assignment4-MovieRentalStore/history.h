#ifndef _HISTORY_H_
#define _HISTORY_H_
#include "command.h"

//History class:	show the history of transaction of a particular customer
//					children class of command
class History : public Command
{
    //print full command
    friend ostream& operator<<(ostream&, const History&);

public:
    //constructor
    History();

    //destructor
    ~History();

    //setter
    bool setData(ifstream& stream);

    //function
    bool processHistory(CustomerDatabase&);

private:
    virtual ostream& out(ostream&) const override;
};
#endif