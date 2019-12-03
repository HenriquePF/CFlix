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
void EntryEdit(int id);

void EntryConfirmation(struct filme movieCheck);

void EntryList(void);
/* -------------------------------------------------------------- */

#endif
