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

// CHANGE FUNCTION NAMES --- OR BETTER COMMENTS;
// FINISH THE EDIT / DELETE FUNCTION;

/* ENTRY Edit Function -- NO FILE! */
void EntryEdit(int index) {
    
    /* Variables */
    struct Array *entryEdit = GetFilmes();
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

/* ----------------- Array Functions ----------------- */
/* ReadId and edit -- NO FILE!*/
void ReadId(int *previousId, int *resultId) {
    int validDigit = 0;
    char userInput[5] = {0};
    int isEmpty = 0;
    
    do {
        
        if (previousId) {
            printf(BOLDBLACK "\nEdit Id[%d]: " RESET, *previousId);
        } else {
            printf(BOLDBLACK "\nRead Id:\n" RESET);
            printf("-> ");
        }
        
        fgets(userInput, sizeof(userInput), stdin);
        fseek(stdin, 0, SEEK_END);
        isEmpty = strcmp(userInput, "\n") == 0;
        validDigit = atoi(userInput);
        
        if (previousId && isEmpty) {
            break;
        }
        
        if (validDigit) {
            *resultId = validDigit;
        } else {
            printf(BOLDRED "Id inválido. Tente novamente.\n" RESET);
        }
        
    } while (!validDigit);
}

/* ReadText and edit -- NO FILE!*/
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

/* ReadDate and edit -- NO FILE!*/
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

/* ReadNumber and edit -- NO FILE!*/
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
            printf(BOLDRED "Número inválido. Tente novamente.\n" RESET);
        }
        
    } while (!validDigit);
}

/* Entry Confirmation -- NO FILES! */
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
        printf(BOLDBLACK "\nId do filme: \n" RESET);
        printf("%d\n", newEntry.entryId);
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
                //                AddFilme(newEntry);
                SaveEntryFile(newEntry);
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

/* Entry List -- File Function INSIDE */
void EntryList() {
    /* Variables */
    struct Array *entries = GetFilmes();
    time_t r;
    struct tm dateStruct = {0};
    char dateFinal[11] = {0}, dateInitial[11] = {0};
    
    r = mktime(&dateStruct);
    strftime(dateInitial, sizeof(dateInitial), "%d/%m/%Y", &dateStruct);
    
    //    RetrieveEntryFile();
    
    if(entries == NULL || entries->count == 0) {
        printf(BOLDRED "\nLISTA VAZIA.\n" RESET);
    } else {
        for (int i = 0; i < entries->count; i++) {
            strftime(dateFinal, sizeof(dateFinal), "%d/%m/%Y", localtime(&entries->p[i].dataLancamento));
            
            //            printf(BOLDRED "\nID: %d)\n" RESET, i + 1);
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
/* Save Entry File Binary Function -- OK */
void SaveEntryFile(struct filme newEntry) {
    FILE *filePtr = 0;
    char *filePath = "./EntryBackup.bin";
    
    filePtr = fopen(filePath, "ab"); // ab for appending in binary - This function will only append
    
    fwrite(&newEntry, sizeof(struct filme), 1, filePtr);
    fclose(filePtr);
}

/* Retrieve Entry Binary File Function -- OK */
void RetrieveEntryFile() {
    char dateRead[11] = {0};
    struct filme readEntry = {0};
    struct tm *dataStruct = {0};
    FILE *filePtr = 0;
    char *filePath = "./EntryBackup.bin";
    
    filePtr = fopen(filePath, "rb"); // rb opens for reading in binary mode, dawg. - This function will only read!
    
    if (!filePtr) {
        printf(BOLDRED "Arquivo inexistente.\n" RESET);
    }
    
    while (fread(&readEntry, sizeof(struct filme), 1, filePtr)) {
        dataStruct = localtime(&readEntry.dataLancamento);
        strftime(dateRead, sizeof(dateRead), "%d/%m/%Y", dataStruct);
        printf("Id: %d \nNome: %s \nData: %s \nDuração: %d\n\n", readEntry.entryId, readEntry.nomeFilme, dateRead, readEntry.duracaoFilme);
    }
    
    fclose(filePtr);
}

// FUNCTION FOR BINARY FILE - TEST & IMPROVE
void EditIdBin() {
    struct filme readEntry = {0};
    int validDigit = 0;
    char userInput[5] = {0};
    int isEmpty = 0;
    FILE *filePtr = 0;
    char *filePath = "./EntryBackup.bin";
    filePtr = fopen(filePath, "wb"); // wb - open for writing in bin mode, shit gets overwritten, dawg.
    
    int localId = readEntry.entryId;
    
    do {
        printf(BOLDBLACK "\nEdit Id[%d]: " RESET, localId);
        
        fgets(userInput, sizeof(userInput), stdin);
        fseek(stdin, 0, SEEK_END);
        isEmpty = strcmp(userInput, "\n") == 0;
        validDigit = atoi(userInput);
        
        if (localId && isEmpty) {
            break;
        }
        
        if (validDigit) {
            readEntry.entryId = validDigit;
            fwrite(&readEntry, sizeof(int), 1, filePtr);
        } else {
            printf(BOLDRED "Id inválido. Tente novamente.\n" RESET);
        }
        
    } while (!validDigit);
    
    fclose(filePtr);
}

// FUNCTION FOR BINARY FILE - TEST & IMPROVE
void EditTextBin() {
    char elementName[199] = {0}, *newString = 0;
    int isEmptyTxt = 0;
    struct filme readEntry = {0};
    FILE *filePtr = 0;
    char *filePath = "./EntryBackup.bin";
    filePtr = fopen(filePath, "wb"); // wb - open for writing in bin mode, shit gets overwritten, dawg.
    char *localText[200] = {0};
    
    strcpy(*localText, readEntry.nomeFilme);
    
    do {
        
        printf(BOLDBLACK "\nEdit  Text [%s]: " RESET, *localText);
        
        fgets(elementName, sizeof(elementName), stdin);
        fseek(stdin, 0, SEEK_END);
        isEmptyTxt = strcmp(elementName, "\n") == 0;
        
        if (*readEntry.nomeFilme && isEmptyTxt) {
            break;
        }
        
        newString = StringTrimmer(elementName);
        
        if (isEmptyTxt && !(*readEntry.nomeFilme)) {
            printf(BOLDRED "Nome inválido. Tente novamente.\n" RESET);
        }
        
        if (!isEmptyTxt) {
            strcpy(readEntry.nomeFilme, newString);
        }
        
        free(newString);
        newString = NULL;
    } while (isEmptyTxt);
    
    fclose(filePtr);
}

// FUNCTION FOR BINARY FILE - TEST & IMPROVE
void EditDateBin() {
    struct filme readEntry = {0};
    FILE *filePtr = 0;
    char *filePath = "./EntryBackup.bin";
    filePtr = fopen(filePath, "wb"); // wb - open for writing in bin mode, shit gets overwritten, dawg.
    char dateRead[11] = {0}, dateTemp[11] = {0};
    int isEmpty = 0, isEqual = 0;
    long localTime = readEntry.dataLancamento;
    
    
    
    do {
        struct tm dataStruct = {0};
        time_t r = 0;
        
        strftime(dateTemp, sizeof(dateTemp), "%d/%m/%Y", localtime(&localTime));
        printf(BOLDBLACK "\nEdit Date[%s]: " RESET, dateTemp);
        
        fgets(dateTemp, 11, stdin);
        isEmpty = strcmp(dateTemp, "\n") == 0;
        fseek(stdin, 0, SEEK_END);
        
        if (isEmpty && localTime) {
            break;
        }
        
        strcpy(dateRead, dateTemp);
        
        strptime(dateTemp, "%d/%m/%Y", &dataStruct);
        r = mktime(&dataStruct);
        strftime(dateTemp, sizeof(dateTemp), "%d/%m/%Y", &dataStruct);
        isEqual = strcmp(dateTemp, dateRead) == 0;
        
        if ((isEmpty && !localTime) || (!isEqual && !localTime) || (!isEqual && localTime)) {
            printf(BOLDRED "Data inválida. Tente novamente.\n" RESET);
        }
        
        if (isEqual && !localTime) {
            readEntry.dataLancamento = r;
            break;
        }
        
        if (isEqual && localTime) {
            readEntry.dataLancamento = r;
            break;
        }
        
    } while (!isEqual);
}

// FUNCTION FOR BINARY FILE - TEST & IMPROVE
void EditDurationBin() {
    struct filme readEntry = {0};
    FILE *filePtr = 0;
    char *filePath = "./EntryBackup.bin";
    filePtr = fopen(filePath, "rb"); // wb - open for writing in bin mode, shit gets overwritten, dawg.
    int validDigit = 0;
    char userInput[5] = {0};
    int isEmpty = 0;
    int localDuration = readEntry.duracaoFilme;
    
    do {
        printf(BOLDBLACK "\nEdit Number[%d]: " RESET, localDuration);
        
        fgets(userInput, sizeof(userInput), stdin);
        isEmpty = strcmp(userInput, "\n") == 0;
        validDigit = atoi(userInput);
        
        if (localDuration && isEmpty) {
            break;
        }
        
        if (validDigit) {
            readEntry.duracaoFilme = validDigit;
        } else {
            printf(BOLDRED "Número inválido. Tente novamente.\n" RESET);
        }
        
    } while (!validDigit);
}

/* Edit Entry File Function */
void EditBinData(int index) { // THEN CHANGE THISSSSSSS
    FILE *filePtr = 0;
    char *filePath = "./EntryBackup.bin";
    filePtr = fopen(filePath, "wb+"); // wb+ - Opens for both reading and writing, if shit already exists, it gets overwritten, dawg! - This function will READ and EDIT(overwrite) entries.
    struct filme readEntry = {0};
    
    /* ID Variables */
    int validDigitId = 0;
    char userInput[5] = {0};
    int isEmptyId = 0;
    /* ------------------ */
    
    /* Text Variables */
    char elementName[199] = {0}, *newString = 0;
    int isEmptyTxt = 0;
    /* ------------------ */
    
    /* Date Variables */
    char dateRead[11] = {0}, dateTemp[11] = {0};
    int isEmpty = 0, isEqual = 0;
    /* ------------------ */
    
    /* Duration Variables */
    int validDigitDuration = 0;
    char userInputDuration[5] = {0};
    int isEmptyDuration = 0;
    /* ------------------ */
    
    /* AFTER the function RetrieveEntryFile is called, hte user will have the option to edit an entry or not... */
    fseek(filePtr, (index - 1) * sizeof(struct filme), SEEK_SET); // Find the struct
    /* fseek will set the user at the position of the wanted entry */
    
    /* fread will read the searched entry and display binary data in the struct format */
    fread(&readEntry, sizeof(struct filme), 1, filePtr);

    /* ID SECTION */
    do {
        if (readEntry.entryId) {
            printf(BOLDBLACK "\nEdit Id[%d]: " RESET, readEntry.entryId);
        } else {
            printf(BOLDBLACK "\nRead Id:\n" RESET);
            printf("-> ");
        }
        
        fgets(userInput, sizeof(userInput), stdin);
        fseek(stdin, 0, SEEK_END);
        isEmptyId = strcmp(userInput, "\n") == 0;
        validDigitId = atoi(userInput);
        
        if (readEntry.entryId && isEmpty) {
            break;
        }
        
        if (validDigitId) {
//            *resultId = validDigit;
        } else {
            printf(BOLDRED "Id inválido. Tente novamente.\n" RESET);
        }
        
    } while (!validDigitId);
    
    /* TEXT SECTION */
    do {
        if (readEntry.nomeFilme) {
            printf(BOLDBLACK "\nEdit  Text [%s]: " RESET, readEntry.nomeFilme);
        } else {
            printf(BOLDBLACK "\nRead Text:\n" RESET);
            printf("-> ");
        }
        
        fgets(elementName, sizeof(elementName), stdin);
        fseek(stdin, 0, SEEK_END);
        isEmptyTxt = strcmp(elementName, "\n") == 0;
        
        if (readEntry.nomeFilme && isEmptyTxt) {
            break;
        }
        
        newString = StringTrimmer(elementName);
        
        if (isEmptyTxt && !readEntry.nomeFilme) {
            printf(BOLDRED "Nome inválido. Tente novamente.\n" RESET);
        }
        
        if (!isEmptyTxt) {
//            strcpy(resultText, newString);
        }
        
        free(newString);
        newString = NULL;
    } while (isEmptyTxt);

    /* DATE SECTION */
    
    do {
        struct tm dataStruct = {0};
        time_t r = 0;
        
        if (readEntry.dataLancamento) {
            strftime(dateTemp, sizeof(dateTemp), "%d/%m/%Y", localtime(readEntry.dataLancamento));
            printf(BOLDBLACK "\nEdit Date[%s]: " RESET, dateTemp);
        } else {
            printf(BOLDBLACK "Read Date\n" RESET);
            printf("-> ");
        }
        
        fgets(dateTemp, 11, stdin);
        isEmpty = strcmp(dateTemp, "\n") == 0;
        fseek(stdin, 0, SEEK_END);
        
        if (isEmpty && readEntry.dataLancamento) {
            break;
        }
        
        strcpy(dateRead, dateTemp);
        
        strptime(dateTemp, "%d/%m/%Y", &dataStruct);
        r = mktime(&dataStruct);
        strftime(dateTemp, sizeof(dateTemp), "%d/%m/%Y", &dataStruct);
        isEqual = strcmp(dateTemp, dateRead) == 0;
        
        if ((isEmpty && !readEntry.dataLancamento) || (!isEqual && !readEntry.dataLancamento) || (!isEqual && readEntry.dataLancamento)) {
            printf(BOLDRED "Data inválida. Tente novamente.\n" RESET);
        }
        
        if (isEqual && !readEntry.dataLancamento) {
//            *resultDate = r;
            break;
        }
        
        if (isEqual && readEntry.dataLancamento) {
//            *resultDate = r;
            break;
        }
        
    } while (!isEqual);
    
    /* DURATION SECTION */
    
    do {
        
        if (readEntry.duracaoFilme) {
            printf(BOLDBLACK "\nEdit Number[%d]: " RESET, readEntry.duracaoFilme);
        } else {
            printf(BOLDBLACK "Read Number:\n" RESET);
            printf("-> ");
        }
        
        fgets(userInputDuration, sizeof(userInputDuration), stdin);
        isEmptyDuration = strcmp(userInputDuration, "\n") == 0;
        validDigitDuration = atoi(userInputDuration);
        
        if (readEntry.duracaoFilme && isEmptyDuration) {
            break;
        }
        
        if (validDigitDuration) {
//            *resultNumbers = validDigit;
        } else {
            printf(BOLDRED "Número inválido. Tente novamente.\n" RESET);
        }
        
    } while (!readEntry.duracaoFilme);
    
//    printf("NOME[%s]: \n", readEntry.nomeFilme);
//    printf("Data[%ld]: \n", readEntry.dataLancamento);
//    printf("DURACAO[%d]: \n", readEntry.duracaoFilme);
    
    fclose(filePtr);
}

/* Delete Entry File Function */
void DeleteEntryFile(int index) {
    FILE *filePtr = 0;
    char *filePath = "./EntryBackup.bin";
    filePtr = fopen(filePath, "wb"); // ab for appending in binary
    
    
    fclose(filePtr);
}
/* ------------ BINARY FILE FUNCTIONS ------------ */
