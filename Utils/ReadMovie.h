#ifndef ReadMovie_h
#define ReadMovie_h

#include <stdio.h>
#include "Filme.h"

void ReadMovieName(char *prevName, struct filme *movie);

void ReadMovieDate(long *prevDate, struct filme *movie);

void ReadMovieDuration(int *prevDuration, struct filme *movie);

#endif
