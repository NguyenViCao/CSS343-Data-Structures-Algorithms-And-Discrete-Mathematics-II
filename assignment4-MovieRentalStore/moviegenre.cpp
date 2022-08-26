#include "moviegenre.h"

//buildMovie: read from input file and create corresponding movie type
Movie* MovieGenre::buildMovie(ifstream& stream)
{
    Movie* newMovie = nullptr;
    char movieType;

    //set movie type
    stream >> movieType;

    //if fail to read movie type
    if (stream.fail()) 
    {
        stream.clear();
        stream.ignore(99, '\n');
        return nullptr;
    }

    //build specific type movie based on the input file
    switch (movieType) 
    {
    case MovieType::ComedyType:
        newMovie = buildMovieComedy(stream);
        break;
    case MovieType::ClassicType:
        newMovie = buildMovieClassic(stream);
        break;
    case MovieType::DramaType:
        newMovie = buildMovieDrama(stream);
        break;
    default:
        error(movieType, stream);
        break;
    }
    return newMovie;
}

//buildMovieComedy: create a comedy type movie from the input file
Movie* MovieGenre::buildMovieComedy (ifstream& stream)
{
    Movie* comedy = new MovieComedy();
    if (comedy->setData(stream))
        return comedy;
    delete comedy;
    return nullptr;
}

//buildMovieDrama: create a drama type movie from the input file
Movie* MovieGenre::buildMovieDrama(ifstream& stream) 
{
    Movie* drama = new MovieDrama();
    if (drama->setData(stream))
        return drama;
    delete drama;
    return nullptr;
}

//buildMovieClassic: create a classic type movie from the input file
Movie* MovieGenre::buildMovieClassic(ifstream& stream) 
{
    Movie* classic = new MovieClassic();
    if (classic->setData(stream))
        return classic;
    delete classic;
    return nullptr;
}

//error: check and show error message to the user if the movie type is not included
void MovieGenre::error(const char& mType, ifstream& stream) 
{
    string fullInfo;
    getline(stream, fullInfo);
    cerr << "Media, type \'" << mType << "\' is not recognized:"
        << '\n' << "  " << mType << fullInfo << endl;
}