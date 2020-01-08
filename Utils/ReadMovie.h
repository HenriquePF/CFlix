#ifndef ReadMovie_h
#define ReadMovie_h

#include <stdio.h>
#include "Filme.h"

/* -------------------------------------------------------------- */

/* Generic Functions */
void ReadId(int *previousId, int *resultId);

void ReadText(char *previousText, char *resultText);

void ReadDate(time_t *previousDate, time_t *resultDate);

void ReadNumber(int *previousNumber, int *resultNumber);
/* Generic Functions */

/* -------------------------------------------------------------- */

/* Movie Functions */
void EntryEdit(int id);

void EntryConfirmation(struct filme movieCheck);

void EntryList(void);
/* Movie Functions */

/* -------------------------------------------------------------- */

/* File Functions */
FILE *OpenFileBinaryMode(void);
void CloseFileBinaryMode(FILE *filePtr);
int IsEmptyFile(FILE *filePtr);
void SaveEntryFile(struct filme newEntry);
void GetEntriesFromFile(void);
int FindEntryById(int entryId);
void EditBinaryData(int index);
void DeleteBinaryData(int index);
//int CheckEntryId(void);
/* File Functions */

/* -------------------------------------------------------------- */
void SearchEntry(int index);

#endif
