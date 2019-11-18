#ifndef ReadMovie_h
#define ReadMovie_h

#include <stdio.h>
#include "Filme.h"

/* -------------------------------------------------------------- */

void ReadText(char *previousText, char **resultText);

void ReadDate(time_t *previousDate, time_t *resultDate);

void ReadNumber(int *previousNumber, int *resultNumber);

/* -------------------------------------------------------------- */

void ReadMovieName(char *prevName, struct filme *movie);

void ReadMovieDate(long *prevDate, struct filme *movie);

void ReadMovieDuration(int *prevDuration, struct filme *movie);

void EditMovie(int id);

void MovieConfirmation(struct filme movieCheck);

void MovieList(void);

#endif


/*
 
 1 - data e duração não salvam;
 2 - Escolher elemento por ID;
 
 */
