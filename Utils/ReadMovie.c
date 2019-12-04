#include <stdlib.h>
#include <string.h>
#include "ReadMovie.h"
#include "Filme.h"
#include "ClearScreen.h"
#include "TrimFunc.h"
#include "TrimFunc.h"
#include "ctype.h"

#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define RESET       "\033[0m"              /* RESET */

/*
 General Ideas....
 
 1 - Case One:
 1.1 - Function to check if file is null(empty or not);
 
 2 - Case Two:
 2.1 - In case of !null, the program will read the file, showing the entries previously saved;
 2.2 - MovieList will be implemented with retrieveEntryFile();
 
 3 - Case Three:
 3.1 - Saves new entries only when user confirms the entry right after MovieConfirmation function;
 3.2 - MovieConfirmation will be implemented with saveEntryFile();
 
 4 - Case Four(Tricky one):
 4.1 - When edition comes to play, it will be edited in the file;
 4.2 - By this point my brain is melting...
 
 --> OBS: Binary files <--
 --> OBS 2: All of the file functions will serve as auxiliary functions for the main ones. <--
 --> OBS 3: Change movie related names to general purpose funciton names! <--
 
 Functions:
 void saveEntryFile(TBD);
 void editBackUpFile(TBD);
 void retrieveEntryFile(TBD);
 void deleteEntryFile(TBD);

 CRUD
 Create - saveEntryFile(TBD);
 Retrieve - retrieveEntryFile(TBD);
 UpDate - editBackUpFile(TBD); -
 Delete - deleteEntryFile(TBD); - The order in the file will change... brain is definitely gone now.

 */

/* --------------- //\\ --------------- */
/* Save Entry File Function */
void saveEntryFile(struct filme newEntry) {
    
    // Every time this functions gets used, it allocates memory for every new entry to be saved.
    
    FILE *filePtr = 0;
    char filePath[60] = "/Users/henriquepetters/Desktop/CFlix/CFlix/EntryBackup.bin";
    // file name: EntryBackup.bin
    filePtr = fopen(filePath, "wb");
    
    // Check?
    if (!filePtr) {
        printf(BOLDRED "Arquivo inexistente.\n" RESET);
    }
    
    // Malloc memory
//    struct filme *teste = malloc(sizeof(struct filme));
//    fwrite(&teste, sizeof(struct filme), 1, filePtr); -> no need to malloc, right?
    
    
    // Writing the structure
    fwrite(&newEntry, sizeof(struct filme), 1, filePtr);
    
    fclose(filePtr);
}

/* Retrieve Entry File Function */
void retrieveEntryFile(struct filme readEntry) {
    FILE *filePtr = 0;
    char filePath[60] = "/Users/henriquepetters/Desktop/CFlix/CFlix/EntryBackup.bin";
    
    filePtr = fopen(filePath, "wb");
    
    // Check?
    if (!filePtr) {
        printf(BOLDRED "Arquivo inexistente.\n" RESET);
    }
    
    fread(&readEntry, sizeof(struct filme) * 3, 1, filePtr);
    printf("Nome: %s \nData(unix): %ld \nDuração: %d", readEntry.nomeFilme, readEntry.dataLancamento, readEntry.duracaoFilme);
    
    fclose(filePtr);
}

/* Edit Entry File Function */
void editBackUpFile() {
    
}

/* Delete Entry File Function */
void deleteEntryFile() {
    
}

/* Check Entry File Function */
void entryFileChecker(struct filme newEntry) {
    int size = 0;
    FILE *filePtr = 0;
    
    filePtr = fopen("EntryBackup.txt", "r+");
    
    if (NULL != filePtr) {
        fseek (filePtr, 0, SEEK_END);
        size = (int)ftell(filePtr);
        
        if (0 == size) {
            printf(BOLDRED "Arquivo vazio.\n" RESET);
        }
    }
}
/* --------------- \\// --------------- */

/* ENTRY Edit Function */
void EntryEdit(int index) {
    
    /* Variables */
    struct Array *entryEdit = GetFilmes();
    struct filme *f = {0};
    f = &(entryEdit->p[index - 1]);
    
    char *nameEdit = f->nomeFilme;
    time_t *dateEdit = &f->dataLancamento;
    int *numEdit = &f->duracaoFilme;
    
    ReadText(f->nomeFilme, nameEdit);
    ReadDate(&f->dataLancamento, dateEdit);
    ReadNumber(&f->duracaoFilme, numEdit);
}

/* ReadText and edit = ok */
void ReadText(char *previousText, char *resultText) {
    char elementName[199] = {0}, *newString = 0;
    int isEmpty = 0;
    
    do {
        if (previousText) {
            printf(BOLDBLACK "\nEdit  Text [%s]: " RESET, previousText);
        } else {
            printf(BOLDBLACK "\nRead Text:\n" RESET);
            printf("-> ");
        }
        
        fgets(elementName, sizeof(elementName), stdin);
        fseek(stdin, 0, SEEK_END);
        isEmpty = strcmp(elementName, "\n") == 0;
        
        if (previousText && isEmpty) {
            break;
        }
        
        newString = StringTrimmer(elementName);
        
        if (isEmpty && !previousText) {
            printf(BOLDRED "Nome inválido. Tente novamente.\n" RESET);
        }
        
        if (!isEmpty) {
            strcpy(resultText, newString);
        }
        
        free(newString);
        newString = NULL;
    } while (isEmpty);
}

/* ReadDate and edit = ok */
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
            printf(BOLDRED "Data inválida. Tente novamente.\n" RESET);
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

/* ReadNumber and edit = ok */
void ReadNumber(int *previousNumber, int *resultNumbers) {
    int validDigit = 0;
    char userInput[5] = {0};
    int isEmpty = 0;
    
    do {
        
        if (previousNumber) {
            printf(BOLDBLACK "\nEdit Number[%d]: " RESET, *previousNumber);
        } else {
            printf(BOLDBLACK "Read Number:\n" RESET);
            printf("-> ");
        }
        
        fgets(userInput, sizeof(userInput), stdin);
        isEmpty = strcmp(userInput, "\n") == 0;
        validDigit = atoi(userInput);
        
        if (previousNumber && isEmpty) {
            break;
        }
        
        if (validDigit) {
            *resultNumbers = validDigit;
        } else {
            printf(BOLDRED "Número inválido. Tente novamente.\n" RESET);
        }
        
    } while (!validDigit);
}

/* Entry Confirmation */
void EntryConfirmation(struct filme newEntry) {
    time_t r;
    struct tm dateStruct = {0};
    char dateFinal[11] = {0}, dateInitial[11] = {0}, confirm = 0;
    
    strptime(dateInitial, "%d/%m/%Y", &dateStruct);
    r = mktime(&dateStruct);
    
    do {
        strftime(dateFinal, sizeof(dateFinal), "%d/%m/%Y", localtime(&newEntry.dataLancamento));
        
        ClearScreen();
        
        printf(BOLDRED "Confirmação de cadastro:\n" RESET);
        printf(BOLDBLACK "\nNome do filme: \n" RESET);
        printf("%s\n\n", newEntry.nomeFilme);
        printf(BOLDBLACK "Data de Lançamento: \n" RESET);
        printf("%s\n\n", dateFinal);
        printf(BOLDBLACK "Duração do filme: \n" RESET);
        printf("%d min\n", newEntry.duracaoFilme);
        printf(BOLDRED "\nSalvar(1) ou descartar(2)?\n" RESET);
        printf("-> ");
        scanf("%c", &confirm);
        fseek(stdin, 0, SEEK_END);
        
        switch (confirm) {
            case '1':
                ClearScreen();
                printf(BOLDRED "Filme salvo!\n" RESET);
                AddFilme(newEntry);
                saveEntryFile(newEntry);
                break;
                
            case '2':
                ClearScreen();
                printf(BOLDRED "\nFilme não salvo.\n" RESET);
                break;
                
            default:
                break;
        }
    } while (confirm != '1' && confirm != '2');
}

/* Entry List */
void EntryList() {
    /* Variables  */
    struct Array *entries = GetFilmes();
    
    
    
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
                retrieveEntryFile(*entries->p);
            printf(BOLDRED "\nID: %d)\n" RESET, i + 1);
            printf(BOLDBLACK "Nome do filme: " RESET);
            printf("%s\n", entries->p[i].nomeFilme);
            printf(BOLDBLACK "Data de lançamento: " RESET);
            printf("%s\n", dateFinal);
            printf(BOLDBLACK "Duração do filme: " RESET);
            printf("%d min\n", entries->p[i].duracaoFilme);
        }
    }
}
