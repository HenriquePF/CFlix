#include <stdlib.h>
#include <string.h>
#include "ReadMovie.h"
#include "Filme.h"
#include "ClearScreen.h"
#include "TrimFunc.h"
#include "TrimFunc.h"
#include "ctype.h"
#include <sys/mman.h>

#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define RESET       "\033[0m"              /* RESET */

const char *g_filePath = "./CFlixRecords.bin";
const char *g_filePathForRemove = "./CFlixRecordsTemp.bin";

/* ----------------- Array Functions ----------------- */
/* ENTRY Edit Function -- ARRAY FUNCTION! -- NOT USED! */
void EntryEdit(int index) {
    
    /* Variables */
    struct Array *entryEdit = GetEntries();
    struct filme *f = {0};
    f = &(entryEdit->p[index - 1]);
    
    int *idEdit = &f->entryId;
    char *nameEdit = f->nomeFilme;
    time_t *dateEdit = &f->dataLancamento;
    int *numEdit = &f->duracaoFilme;
    
    ReadId(&f->entryId, idEdit);
    ReadText(f->nomeFilme, nameEdit);
    ReadDate(&f->dataLancamento, dateEdit);
    ReadNumber(&f->duracaoFilme, numEdit);
}

/* ReadId and edit -- ARRAY FUNCTION! -- AUX. FOR FILE FUNCTIONS */
void ReadId(int *previousId, int *resultId) {
    int validDigit = 0, isEmpty = 0;
    char userInput[5] = {0};
    FILE *getFile = 0;
    struct filme readId = {0};
    getFile = OpenFileBinaryMode();
    
    // check if new id exists
    do {
        if (previousId) {
            printf(BOLDBLACK "\nEdit Id[%d]: " RESET, *previousId);
        } else {
            printf(BOLDBLACK "\nRead Id:\n" RESET);
            printf("-> ");
        }
        
        fgets(userInput, sizeof(userInput), stdin);
        isEmpty = strcmp(userInput, "\n") == 0;
        validDigit = atoi(userInput);
        
        // Check for matching ID's
        while (fread(&readId, sizeof(struct filme), 1, getFile)) {
            if (validDigit == readId.entryId) {
                printf(BOLDRED "\nId already exists. Choose another FIRST.\n" RESET);
                break;
            }
        }
        
        // if it's NOT empty AND the valid digit IS equal to readId.entryId - OK
        if (!isEmpty && (validDigit == readId.entryId)) {
            printf(BOLDRED "\nId already exists. Choose another SECOND.\n" RESET);
        }
        
        
        // If there IS a previous and it is empty = it will carry the old value - OK
        if (previousId && isEmpty) {
            break;
        }
        
        // if the value is valid and the valid digit IS NOT equal to readId.entryId = it will update the value - OK
        if (validDigit && validDigit != readId.entryId) {
            *resultId = validDigit;
        } else {
            printf(BOLDRED "Invalid ID. Try again.\n" RESET);
        }
        
        fseek(getFile, sizeof(struct filme), SEEK_SET);
    } while (!validDigit || (validDigit == readId.entryId) || (!isEmpty && (validDigit == readId.entryId)));
    CloseFileBinaryMode(getFile);
}

/* ReadText and edit -- ARRAY FUNCTION! -- AUX. FOR FILE FUNCTIONS */
void ReadText(char *previousText, char *resultText) {
    char elementName[199] = {0}, *newString = 0;
    int isEmpty = 0, isEmptyLine = 0;
    
    do {
        if (previousText) {
            printf(BOLDBLACK "\nEdit Text[%s]: " RESET, previousText);
        } else {
            printf(BOLDBLACK "\nRead Text:\n" RESET);
            printf("-> ");
        }
        
        fgets(elementName, sizeof(elementName), stdin);
        fseek(stdin, 0, SEEK_END);
        isEmpty = strcmp(elementName, "\n") == 0;
        isEmptyLine = strcmp(elementName, " ") == 0;
        
        if (previousText && isEmpty) {
            break;
        }
        
        if (isEmptyLine) {
            printf(BOLDRED "TA VAZIO CUZAUM!.\n" RESET);
        }
        
        newString = StringTrimmer(elementName);
        
        if (isEmpty && !previousText) {
            printf(BOLDRED "Invalid text. Try again.\n" RESET);
        }
        
        if (!isEmpty) {
            strcpy(resultText, newString);
        }
        
        free(newString);
        newString = NULL;
    } while (isEmpty);
}

/* ReadDate and edit -- ARRAY FUNCTION! -- AUX. FOR FILE FUNCTIONS */
void ReadDate(time_t *previousDate, time_t *resultDate) {
    char dateRead[11] = {0}, dateTemp[11] = {0};
    int isEmpty = 0, isEqual = 0;
    
    do {
        struct tm dataStruct = {0};
        time_t r = 0;
        
        if (previousDate) {
            strftime(dateTemp, sizeof(dateTemp), "%d/%m/%Y", localtime(previousDate));
            printf(BOLDBLACK "\nEdit Date[%s]: " RESET, dateTemp);
        } else {
            printf(BOLDBLACK "Read Date\n" RESET);
            printf("-> ");
        }
        
        fgets(dateTemp, 11, stdin);
        isEmpty = strcmp(dateTemp, "\n") == 0;
        fseek(stdin, 0, SEEK_END);
        
        if (isEmpty && previousDate) {
            break;
        }
        
        strcpy(dateRead, dateTemp);
        
        strptime(dateTemp, "%d/%m/%Y", &dataStruct);
        r = mktime(&dataStruct);
        strftime(dateTemp, sizeof(dateTemp), "%d/%m/%Y", &dataStruct);
        isEqual = strcmp(dateTemp, dateRead) == 0;
        
        if ((isEmpty && !previousDate) || (!isEqual && !previousDate) || (!isEqual && previousDate)) {
            printf(BOLDRED "Invalid date. Try again.\n" RESET);
        }
        
        if (isEqual && !previousDate) {
            *resultDate = r;
            break;
        }
        
        if (isEqual && previousDate) {
            *resultDate = r;
            break;
        }
        
    } while (!isEqual);
}

/* ReadNumber and edit -- ARRAY FUNCTION! -- AUX. FOR FILE FUNCTIONS */
void ReadNumber(int *previousNumber, int *resultNumbers) {
    int validDigit = 0;
    char userInputDuration[5] = {0};
    int isEmptyDuration = 0;
    
    do {
        
        if (previousNumber) {
            printf(BOLDBLACK "\nEdit Number[%d]: " RESET, *previousNumber);
        } else {
            printf(BOLDBLACK "Read Number:\n" RESET);
            printf("-> ");
        }
        
        fgets(userInputDuration, sizeof(userInputDuration), stdin);
        isEmptyDuration = strcmp(userInputDuration, "\n") == 0;
        validDigit = atoi(userInputDuration);
        
        if (previousNumber && isEmptyDuration) {
            break;
        }
        
        if (validDigit) {
            *resultNumbers = validDigit;
        } else {
            printf(BOLDRED "Invalid number. Try again.\n" RESET);
        }
        fseek(stdin, 0, SEEK_END);
    } while (!validDigit);
}

/* Entry Confirmation -- ARRAY FUNCTION! -- AUX. FOR FILE FUNCTIONS */
void EntryConfirmation(struct filme newEntry) {
    time_t r;
    struct tm dateStruct = {0};
    char dateFinal[11] = {0}, dateInitial[11] = {0}, confirm = 0;
    
    strptime(dateInitial, "%d/%m/%Y", &dateStruct);
    r = mktime(&dateStruct);
    
    do {
        strftime(dateFinal, sizeof(dateFinal), "%d/%m/%Y", localtime(&newEntry.dataLancamento));
        
        ClearScreen();
        
        printf(BOLDRED "Entry Confirmation:\n" RESET);
        printf(BOLDBLACK "\nEntry ID: \n" RESET);
        printf("%d\n", newEntry.entryId);
        printf(BOLDBLACK "\nEntry Text: \n" RESET);
        printf("%s\n\n", newEntry.nomeFilme);
        printf(BOLDBLACK "Date: \n" RESET);
        printf("%s\n\n", dateFinal);
        printf(BOLDBLACK "Number: \n" RESET);
        printf("%d min\n", newEntry.duracaoFilme);
        printf(BOLDRED "\nSave(1) ou Discard(2)?\n" RESET);
        printf("-> ");
        scanf("%c", &confirm);
        fseek(stdin, 0, SEEK_END);
        
        switch (confirm) {
            case '1':
                ClearScreen();
                printf(BOLDRED "Entry saved!\n" RESET);
                
                SaveEntryFile(newEntry);
                break;
                
            case '2':
                ClearScreen();
                printf(BOLDRED "\nEntry discated.\n" RESET);
                break;
                
            default:
                break;
        }
    } while (confirm != '1' && confirm != '2');
}

/* Entry List -- File Function INSIDE -- NOT USED! */
void EntryList() {
    /* Variables */
    struct Array *entries = GetEntries();
    time_t r;
    struct tm dateStruct = {0};
    char dateFinal[11] = {0}, dateInitial[11] = {0};
    
    r = mktime(&dateStruct);
    strftime(dateInitial, sizeof(dateInitial), "%d/%m/%Y", &dateStruct);
    
    
    if(entries == NULL || entries->count == 0) {
        printf(BOLDRED "\nLISTA VAZIA.\n" RESET);
    } else {
        for (int i = 0; i < entries->count; i++) {
            strftime(dateFinal, sizeof(dateFinal), "%d/%m/%Y", localtime(&entries->p[i].dataLancamento));
            
            printf(BOLDBLACK "\nId do Filme: " RESET);
            printf("%d\n", entries->p[i].entryId);
            printf(BOLDBLACK "Nome do filme: " RESET);
            printf("%s\n", entries->p[i].nomeFilme);
            printf(BOLDBLACK "Data de lançamento: " RESET);
            printf("%s\n", dateFinal);
            printf(BOLDBLACK "Duração do filme: " RESET);
            printf("%d min\n", entries->p[i].duracaoFilme);
        }
    }
}
/* ----------------- Array Functions ----------------- */

/* ------------ BINARY FILE FUNCTIONS ------------ */

/* Opens file in RB mode */
FILE *OpenFileBinaryMode() {
    FILE *filePtr = 0;
    filePtr = fopen(g_filePath, "rb");
    
    if (!filePtr) {
        filePtr = fopen(g_filePath, "ab");
    }
    
    return filePtr;
}

/* Close ReadFileBinaryMode */
void CloseFileBinaryMode(FILE *filePtr) {
    fclose(filePtr);
}

/* Checks if file has content */
int IsEmptyFile(FILE *filePtr) {
    struct filme entries = {0};
    
    if (filePtr == NULL) {
        return 1;
    } else if (fread(&entries, sizeof(struct filme), 1, filePtr) == 0) {
        return 2;
    }
    return 0;
}

/* Save Entry File Binary Function -- OK */
void SaveEntryFile(struct filme newEntry) {
    FILE *filePtr = 0;
    
    filePtr = fopen(g_filePath, "ab"); // ab for appending in binary - This function will only append, dawg!
    
    fwrite(&newEntry, sizeof(struct filme), 1, filePtr);
    fclose(filePtr);
}

/* Retrieve Entry Binary File Function -- OK */
void GetEntriesFromFile() {
    char dateRead[11] = {0};
    struct filme readEntry = {0};
    struct tm *dataStruct = {0};
    FILE *filePtr = 0;
    
    filePtr = fopen(g_filePath, "rb"); // rb opens for reading in binary mode, dawg.
    
    while (fread(&readEntry, sizeof(struct filme), 1, filePtr)) {
        dataStruct = localtime(&readEntry.dataLancamento);
        strftime(dateRead, sizeof(dateRead), "%d/%m/%Y", dataStruct);
        printf("\nId: %d \nText: %s \nDate: %s \nNumber: %d\n\n", readEntry.entryId, readEntry.nomeFilme, dateRead, readEntry.duracaoFilme);
    }
    fclose(filePtr);
}

// Used for Edit and Delete
int FindEntryById(int inputId) {
    int entryIndex = 1; // starts with 1
    FILE *filePtr = 0;
    filePtr = fopen(g_filePath, "rb");
    struct filme readEntry = {0};
    
    while (fread(&readEntry, sizeof(struct filme), 1, filePtr)) {
        
        // Input is compared with element, if matched, it returns it's index
        if (readEntry.entryId == inputId) {
            return entryIndex;
        }
        entryIndex++;
    }
    
    return -1;
}

/* Edit Entry File Function */
void EditBinaryData(int index) {
    int newIndex = 0;
    FILE *filePtr = 0;
    struct filme readEntry = {0};
    filePtr = fopen(g_filePath, "rb+");
    
    newIndex = FindEntryById(index);
    
    if (newIndex != -1) {
        /* fseek will set the user at the position of the wanted entry */
        fseek(filePtr, (newIndex - 1) * sizeof(struct filme), SEEK_SET); // Find the struct
        
        /* fread will read the searched entry and display binary data in the struct format */
        fread(&readEntry, sizeof(struct filme), 1, filePtr);
        
        ReadId(&readEntry.entryId, &readEntry.entryId);
        
        // check if new id exists
        
        ReadText(readEntry.nomeFilme, readEntry.nomeFilme);
        ReadDate(&readEntry.dataLancamento, &readEntry.dataLancamento);
        ReadNumber(&readEntry.duracaoFilme, &readEntry.duracaoFilme);
        
        /* fseek back one element so fwrite is executed at the right spot */
        fseek(filePtr, (newIndex - 1) * sizeof(struct filme), SEEK_SET);
        
        /* fwrite the new element in the right spot */
        fwrite(&readEntry, sizeof(struct filme), 1, filePtr);
        
    } else {
        printf(BOLDRED "\nEntry not found!\n" RESET);
        
    }
    
    fclose(filePtr);
}

/* Delete Entry File Function */
void DeleteBinaryData(int inputId) {
    int indexDelete = 0;
    FILE *filePtr = 0; /* For Reading */
    FILE *filePtrTemp = 0; /* For Writing */
    struct filme readEntry = {0};
    
    filePtr = fopen(g_filePath, "rb"); /* Main file will get read - if file doesn't exist, returns NULL */
    filePtrTemp = fopen(g_filePathForRemove, "wb"); /* Second file will be written - If file doesn't exist, it'll create one*/
    
    indexDelete = FindEntryById(inputId);
    
    if (indexDelete != -1) {
        /* while there is entries to read */
        while (fread(&readEntry, sizeof(struct filme), 1, filePtr)) {
            if (inputId == readEntry.entryId) { /* if inputId matches the entry id, the entry will get ignored */
            } else {
                fwrite(&readEntry, sizeof(struct filme), 1, filePtrTemp); /* everything else will be written in the new file */
            }
        }
        
        fclose(filePtr); /* Close both files */
        fclose(filePtrTemp);
        remove("CFlixRecords.bin"); /* Main file gets removed - It contains all the entries */
        rename("CFlixRecordsTemp.bin", "CFlixRecords.bin"); /* New file gets the main file name */
        
    } else {
        printf(BOLDRED "\nEntry not found!\n" RESET);
    }
}
/* ------------ BINARY FILE FUNCTIONS ------------ */
