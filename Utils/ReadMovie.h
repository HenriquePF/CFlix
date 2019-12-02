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
void EditMovie(int id);

void MovieConfirmation(struct filme movieCheck);

void MovieList(void);
/* -------------------------------------------------------------- */

#endif
