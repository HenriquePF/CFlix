#ifndef ReadMovie_h
#define ReadMovie_h

#include <stdio.h>
#include "Filme.h"

/* -------------------------------------------------------------- */
// Generic Functions
void ReadId(int *previousId, int *resultId);

void ReadText(char *previousText, char *resultText);

void ReadDate(time_t *previousDate, time_t *resultDate);

void ReadNumber(int *previousNumber, int *resultNumber);
/* -------------------------------------------------------------- */
// Movie Functions
void EntryEdit(int id);

void EntryConfirmation(struct filme movieCheck);

void EntryList(void);
/* -------------------------------------------------------------- */

/* File Functions */
void SaveEntryFile(struct filme newEntry);
void RetrieveEntryFile(void);
void EditBackUpFile(struct Array removeEntry, int index);
void DeleteEntryFile(void);
/* -------------------------------------------------------------- */
#endif
