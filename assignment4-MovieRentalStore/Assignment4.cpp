#include <iostream>
#include <fstream>
#include <ostream>
#include "storemanager.h"
#include "bst.h"
using namespace std;

int main() 
{
    //create the StoreManager class
    StoreManager StoreManager;

    //read the data for customers, movies, and commands
    ifstream customerFile("data4customers.txt"),    // customer file
            movieFile("data4movies.txt"),           // movies file
            commandFile("data4commands.txt");       // command file

    //reads customers information from provided text file
    StoreManager.buildCustomers(customerFile);

    //reads movies from provided text file
    StoreManager.buildMovies(movieFile);

    //reads commands from provided text file
    StoreManager.processCommands(commandFile);

    system("pause");
    return 0;
}