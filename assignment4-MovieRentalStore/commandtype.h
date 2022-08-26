#ifndef _COMMANDTYPE_H_
#define _COMMANDTYPE_H_
#include <iomanip>
#include "command.h"
#include "borrow.h"
#include "return.h"
#include "history.h"
#include "inventory.h"


//CommandType class:	reads the input file, create 4 different type of Command objects 
//	    				including borrow, return, show history, and show inventory

class CommandType
{
public:
    //read the input file of Commands
    static Command* createCommand(ifstream& stream);

private:
    //if input from command is B, create a new borrow command
    static Command* createBorrow(ifstream& stream);

    //if input from command is R, create a new return command
    static Command* createReturn(ifstream& stream);

    //if input from command is H, create a new history command
    static Command* createHistory(ifstream& stream);

    //if input from command is I, create a new inventory command
    static Command* createInventory(ifstream& stream);

    //check for unexpected command types
    static void error(const char& cType, ifstream& stream);
};
#endif