#ifndef ReadMovie_h
#define ReadMovie_h

#include <stdio.h>
#include "Filme.h"

/* -------------------------------------------------------------- */
// Generic Functions
void ReadText(char *previousText, char *resultText);

void ReadDate(time_t *previousDate, time_t *resultDate);

void ReadNumber(int *previousNumber, int *resultNumber);

/* -------------------------------------------------------------- */
// Movie Functions
void ReadMovieName(char *prevName, struct filme *movie);

void ReadMovieDate(long *prevDate, struct filme *movie);

void ReadMovieDuration(int *prevDuration, struct filme *movie);

void EditMovie(int id);

void MovieConfirmation(struct filme movieCheck);

void MovieList(void);

#endif
