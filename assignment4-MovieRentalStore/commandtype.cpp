#include "commandtype.h"

//createCommand create the command object in general
Command* CommandType::createCommand(ifstream& stream)
{
    Command* newCommand = nullptr;
    char commandType;
    stream >> commandType;

    //fail to read movie type
    if (stream.fail()) 
    {
        stream.clear();
        stream.ignore(99, '\n');
        return nullptr;
    }

    // specific type
    switch (commandType) 
    {
        //borrow case
    case CommandCase::BorrowCase:
        newCommand = createBorrow(stream);
        break;

        //return case
    case CommandCase::ReturnCase:
        newCommand = createReturn(stream);
        break;

        //history case
    case CommandCase::HistoryCase:
        newCommand = createHistory(stream);
        break;

        //inventory case
    case CommandCase::InventoryCase:
        newCommand = createInventory(stream);
        break;

        //error case
    default:
        error(commandType, stream);
        break;
    }

    // return pointer of command
    return newCommand;
}

//createBorrow: creates the borrow object
Command* CommandType::createBorrow(ifstream& stream) 
{
    //create borrow obj
    Borrow* cBorrow = new Borrow();
    cBorrow->setCommandType(CommandCase::BorrowCase);
    if (cBorrow->setData(stream)) 
        return cBorrow;

    delete cBorrow;
    return nullptr;
}

//createReturn: creates the return object
Command* CommandType::createReturn(ifstream& stream) 
{
    Return* cReturn = new Return();
    cReturn->setCommandType(CommandCase::ReturnCase);
    if (cReturn->setData(stream))
        return cReturn;

    delete cReturn;
    return nullptr;
}

//createHistory: creates the history object
Command* CommandType::createHistory(ifstream& stream) 
{
    History* cHistory = new History();
    cHistory->setCommandType(CommandCase::HistoryCase);
    if (cHistory->setData(stream))
        return cHistory;

    delete cHistory;
    return nullptr;
}

//createInventory: creates the inventory object
Command* CommandType::createInventory(ifstream& stream) 
{
    Inventory* cInventory = new Inventory();
    return cInventory;
}

//error: show error of error type
void CommandType::error(const char& cType, ifstream& stream) 
{
    string fullCommand;
    getline(stream, fullCommand, '\n');
    cerr << "Command, invalid command type '" << cType << "':"
        << '\n' << "  " << cType << fullCommand << endl;
}