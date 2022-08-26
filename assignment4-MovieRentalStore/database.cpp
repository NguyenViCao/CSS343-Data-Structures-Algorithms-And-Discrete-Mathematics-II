#include "database.h"

//constructor
Database::Database() 
{
    //nested specific type of movie into movie collection
    //set comedy type
    movies.insert(pair<MovieType, BST<InventoryDatabase>>(MovieType::ComedyType, comedies));

    //set classic type
    movies.insert(pair<MovieType, BST<InventoryDatabase>>(MovieType::ClassicType, classics));

    //set drama type
    movies.insert(pair<MovieType, BST<InventoryDatabase>>(MovieType::DramaType, dramas));
}

//destructor
Database::~Database(){}

//insert the media type to the database
bool Database::insert(InventoryDatabase* media)
{
    //check movie type
    if(media->getMediaType() == MediaType::DVDMovie)
        return insertMovie(media);

    // media type is not exist
    return false;
}

//insertMovie helper use insert movie to the database
bool Database::insertMovie(InventoryDatabase* movie)
{
    MovieType type = dynamic_cast<Movie*>(movie)->getMovieType();

    //insert comedy
    if (type == MovieType::ComedyType)
        return movies.at(MovieType::ComedyType).insert(movie);

    //insert classic
    else if (type == MovieType::ClassicType)
        return movies.at(MovieType::ClassicType).insert(movie);

    //insert drama
    else if (type == MovieType::DramaType)
        return movies.at(MovieType::DramaType).insert(movie);

    //else, movie type is not exist
    else
        return false;
}

//retrieve return the target media
bool Database::retrieve(const InventoryDatabase& target, InventoryDatabase*& retriever)
{
    //find the media type
    if (target.getMediaType() == MediaType::DVDMovie) 
    {
        return retrieveMovie(target, retriever);
    }

    //else, media type is not exist
    return false;
}

//retrieveMovie helperfunction to retrieve the target movie in the database
bool Database::retrieveMovie(const InventoryDatabase& target, InventoryDatabase*& retriever)
{
    MovieType type = dynamic_cast<const Movie&>(target).getMovieType();

    //find and return if it is comedy
    if (type == MovieType::ComedyType)
        return movies.at(MovieType::ComedyType).retrieve(target, retriever);

    //find and return if it is classic
    else if (type == MovieType::ClassicType) 
        return movies.at(MovieType::ClassicType).retrieve(target, retriever);

    //find and return if it is drama
    else if (type == MovieType::DramaType) 
        return movies.at(MovieType::DramaType).retrieve(target, retriever);

    //else, movie type is not exist
    else 
        return false;
}

//remove the media type from the database
bool Database::remove(const InventoryDatabase& target)
{
    //look for the media type
    if (target.getMediaType() == MediaType::DVDMovie)
        return removeMovie(target);

    //else media type is not exist
    return false;
}

//removeMovie helper function to remove the DVDMovie from database
bool Database::removeMovie(const InventoryDatabase& target)
{
    //find if it is comedy
    if (dynamic_cast<const Movie&>(target).getMovieType() == MovieType::ComedyType)
        return movies.at(MovieType::ComedyType).remove(target);

    //find if it is classic
    else if (dynamic_cast<const Movie&>(target).getMovieType() == MovieType::ClassicType)
        return movies.at(MovieType::ClassicType).remove(target);

    //find if it is drama
    else if (dynamic_cast<const Movie&>(target).getMovieType()== MovieType::DramaType)
        return movies.at(MovieType::DramaType).remove(target);

    //else, movie type is not exist
    else
        return false;
}

//display all the elements in database
void Database::display() const
{
    movies.at(MovieType::ComedyType).display();
    movies.at(MovieType::DramaType).display();
    movies.at(MovieType::ClassicType).display();
}

//return the number of media in the database 
int Database::getTotalMedia() const
{
    return getTotalMovie();
}

//getTotalMovie: helper method for getTotalMedia
int Database::getTotalMovie() const
{
    int t = movies.at(MovieType::ComedyType).getTotalNode() + movies.at(MovieType::DramaType).getTotalNode() + movies.at(MovieType::ClassicType).getTotalNode();
    return t;
}