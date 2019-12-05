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

/* --------------- XXX --------------- */

/* Save Entry File Function */
void saveEntryFile(struct filme newEntry) {
    FILE *filePtr = 0;
    char filePath[60] = "/Users/henriquepetters/Desktop/CFlix/CFlix/EntryBackup.bin";
    filePtr = fopen(filePath, "wb"); // should be "rb"
    
    fwrite(&newEntry, sizeof(struct filme), 1, filePtr);
    fclose(filePtr);
}

/* Retrieve Entry File Function */
void retrieveEntryFile(struct filme readEntry) {
    char dateRead[11] = {0};
    struct tm *dataStruct = localtime(&readEntry.dataLancamento);
    FILE *filePtr = 0;
    char filePath[60] = "/Users/henriquepetters/Desktop/CFlix/CFlix/EntryBackup.bin";
    
    filePtr = fopen(filePath, "rb");
    
    if (!filePtr) {
        printf(BOLDRED "Arquivo inexistente.\n" RESET);
    }
    
    fread(&readEntry, sizeof(struct filme), 1, filePtr);
    strftime(dateRead, sizeof(dateRead), "%d/%m/%Y", dataStruct);
    printf("Nome: %s \nData: %s \nDuração: %d\n\n", readEntry.nomeFilme, dateRead, readEntry.duracaoFilme);
    fseek(filePtr, sizeof(struct filme), SEEK_CUR);
    
    fclose(filePtr);
}

/* Edit Entry File Function */
void editBackUpFile() {
    
}

/* Delete Entry File Function */
void deleteEntryFile() {
    
}
/* --------------- XXX --------------- */

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
