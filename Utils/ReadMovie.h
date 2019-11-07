#ifndef ReadMovie_h
#define ReadMovie_h

#include <stdio.h>
#include "Filme.h"

void ReadMovieName(char *prevName, struct filme *movie);

void ReadMovieDate(long *prevDate, struct filme *movie);

void ReadMovieDuration(int *prevDuration, struct filme *movie);

<<<<<<< HEAD
void EditMovie(int id);

void MovieConfirmation(struct filme movieCheck);

void MovieList(void);

=======
>>>>>>> 273ee77a5cfdc30de593f8191f8d4900e92564c4
#endif
