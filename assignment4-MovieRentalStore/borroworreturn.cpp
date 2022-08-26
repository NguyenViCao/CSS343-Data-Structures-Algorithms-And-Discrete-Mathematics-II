#include "borroworreturn.h"
//constructor
BorrowOrReturn::BorrowOrReturn() 
{
	this->customerID = kDEFAULT_ID;
	this->mediaType = DefaultMediaType;
	this->movieType = DefaultMovieType;
	this->media = nullptr;
}

//destructor
BorrowOrReturn::~BorrowOrReturn() 
{
	if (this->media != nullptr) 
	{
		delete this->media;
		this->media = nullptr;
	}
}

bool BorrowOrReturn::setData(ifstream& stream) 
{
	//create media, and some temporary data
	InventoryDatabase* aMedia = nullptr;

	//parameters use to read data from file
	char tempMedia;
	char tempMovie;
	string tempID;

	//assign comment type to command
	fullCommand = this->commandCase;
	fullCommand += ' ';

	//assign customer ID to command
	stream.ignore();
	stream >> tempID;
	fullCommand += tempID;
	fullCommand += ' ';

	//use to convert string to number
	stringstream convert(tempID);
	convert >> this->customerID;

	//if customer id is invalid
	if(convert.fail() || customerID < 0) 
	{
		processError(stream, tempID, string("customer ID"));
		return false;
	}

	//read media type
	stream.ignore();
	stream >> tempMedia;

	//assign media type to command
	fullCommand += tempMedia;
	fullCommand += ' ';

	//check type of media
	switch (tempMedia) 
	{
		//movie media
	case DVDMovie:
		this->mediaType = DVDMovie;

		//read file
		stream.ignore();
		stream >> tempMovie;

		//assign movie type to command
		fullCommand += tempMovie;
		fullCommand += ' ';

		// check type of movie
		switch (tempMovie) 
		{
			//comedy case
		case ComedyType:
			processComedy(stream, aMedia);
			break;

			//classic case
		case ClassicType:
			processClassic(stream, aMedia);
			break;

			//drama case
		case DramaType:
			processDrama(stream, aMedia);
			break;

			//invalid movie type
		default:
			processError(stream,string().insert(0, 1, tempMovie),string("movie type"));
			break;
		}
		break;

		// invalid media type
	default:
		processError(stream,string().insert(0, 1, tempMedia),string("media type"));
		break;
	}

	//clear the stream pipe
	stream.clear();

	// assign this media
	this->media = aMedia;
	bool isValid = this->media != nullptr ? isValid = true : isValid = false;
	return isValid;
}

//processComedy: process the command for movie comedy type
void BorrowOrReturn::processComedy(ifstream& stream, InventoryDatabase*& aMedia) 
{
	this->movieType = ComedyType;
	aMedia = new MovieComedy();
	string tempTitle;
	int tempYear;

	// set title
	stream.ignore();
	getline(stream >> ws, tempTitle, ',');
	dynamic_cast<MovieComedy*>(aMedia)->setTitle(tempTitle);

	//set year
	stream.ignore();
	stream >> tempYear;
	dynamic_cast<MovieComedy*>(aMedia)->setYear(tempYear);

	// add to command
	fullCommand += tempTitle + ", " + to_string(tempYear);
}

//processClassic: process command for movie classic
void BorrowOrReturn::processClassic(ifstream& stream, InventoryDatabase*& aMedia) 
{
	this->movieType = ClassicType;
	aMedia = new MovieClassic();
	string tempActorFirst;
	string tempActorLast;
	int tempMonth;
	int tempYear;

	//set month
	stream.ignore();
	stream >> tempMonth;
	dynamic_cast<MovieClassic*>(aMedia)->setMonth(tempMonth);

	//set year
	stream.ignore();
	stream >> tempYear;
	dynamic_cast<MovieClassic*>(aMedia)->setYear(tempYear);

	//set actor first name
	stream.ignore();
	stream >> tempActorFirst;
	dynamic_cast<MovieClassic*>(aMedia)->setMajorActorFirst(tempActorFirst);

	//set actor last name
	stream.ignore();
	stream >> tempActorLast;
	dynamic_cast<MovieClassic*>(aMedia)->setMajorActorLast(tempActorLast);

	//add to command
	fullCommand += to_string(tempMonth)
		+ ' ' + to_string(tempYear)
		+ ' ' + tempActorFirst
		+ ' ' + tempActorLast;
}

// processDrama: process command for movie drama
void BorrowOrReturn::processDrama(ifstream& stream, InventoryDatabase*& aMedia) 
{
	this->movieType = DramaType;
	aMedia = new MovieDrama();
	string tempTitle;
	string tempDirector;

	// set media director
	stream.ignore();
	getline(stream >> ws, tempDirector, ',');
	dynamic_cast<MovieDrama*>(aMedia)->setDirector(tempDirector);

	//set media title
	stream.ignore();
	getline(stream >> ws, tempTitle, ',');
	dynamic_cast<MovieDrama*>(aMedia)->setTitle(tempTitle);

	//add to command
	fullCommand += tempDirector + ", " + tempTitle + ", ";
}

//processInvalid: in charge of invalid customer id, media type, movie type
void BorrowOrReturn::processError(ifstream& stream,const string& error,const string& message) 
{
	string temp;
	stream.ignore();
	getline(stream, temp, '\n');
	this->fullCommand += temp;

	// print error message
	cerr << "Command, invalid " << message << " '" << error << "':"
		<< '\n' << "  " << this->fullCommand << endl;
}

//out: use to set ostream data
ostream& BorrowOrReturn::out(ostream& out) const 
{
	out << (char)this->commandCase;
	return out;
}

//operator<<: print the command data
ostream& operator<<(ostream& stream, const BorrowOrReturn& command) 
{
	command.out(stream);
	return stream;
}