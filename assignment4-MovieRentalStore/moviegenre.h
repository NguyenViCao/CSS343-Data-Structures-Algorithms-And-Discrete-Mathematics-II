#ifndef _MOVIE_GENRE_H_
#define _MOVIE_GENRE_H_
#include "movie.h"
#include "moviecomedy.h"
#include "moviedrama.h"
#include "movieclassic.h"

/*
MovieGenre class:	use to create different types of movie objects
					create comedy obj, drama obj, and classic obj
*/
class MovieGenre
{
public:
	//read the input file and create the corresponding movie object
	static Movie* buildMovie(ifstream& stream);

private:
	//read the character assigned to movie type, F is comedy movie
	static Movie* buildMovieComedy (ifstream& stream);

	//read the character assigned to movie type, D is drama movie
	static Movie* buildMovieDrama(ifstream& stream);

	//read the character assigned to movie type, C is classic movie
	static Movie* buildMovieClassic(ifstream& stream);

	//exception for error
	static void error(const char& type, ifstream& stream);
};
#endif