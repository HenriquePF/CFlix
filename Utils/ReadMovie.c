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

/* Movie Edit Function */
void EditMovie(int index) {
    
    /* Variables */
    struct Array *movieEdit = GetFilmes();
    struct filme *f = {0};
    f = &((movieEdit->p[index - 1]));
    
    char *nameEdit = f->nomeFilme;
    time_t *dateEdit = &f->dataLancamento;
    int *numEdit = &f->duracaoFilme;
    
    ReadText(f->nomeFilme, nameEdit);
    ReadDate(&f->dataLancamento, dateEdit);
    ReadNumber(&f->duracaoFilme, numEdit);
}

/* ReadText and edit = ok */
void ReadText(char *previousText, char *resultText) {
    char movieName[199] = {0}, *newString = 0;
    int isEmpty = 0;
    
    do {
        if (previousText) {
            printf(BOLDBLACK "\nRead Text [%s]: " RESET, previousText);
        } else {
            printf(BOLDBLACK "\nRead Text:\n" RESET);
            printf("-> ");
        }
        
        fgets(movieName, sizeof(movieName), stdin);
        fseek(stdin, 0, SEEK_END);
        isEmpty = strcmp(movieName, "\n") == 0;
        
        if (previousText && isEmpty) {
            break;
        }
        
        newString = StringTrimmer(movieName);
        
        if (!previousText && isEmpty) {
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
    int isEmpty = 0;
    
    do {
        struct tm dataStruct = {0};
        time_t r = 0;
        
        if (previousDate) {
            strftime(dateTemp, sizeof(dateTemp), "%d/%m/%Y", localtime(previousDate));
            printf(BOLDBLACK "\nRead Date[%s]: " RESET, dateTemp);
        } else {
            printf(BOLDBLACK "Read Date\n" RESET);
            printf("-> ");
        }
        
        fgets(dateTemp, 11, stdin);
        isEmpty = strcmp(dateTemp, "\n") == 0;
        fseek(stdin, 0, SEEK_END);
        
        if (!previousDate && isEmpty) {
            printf(BOLDRED "Data inválida. Tente novamente.\n" RESET);
        }
        
        if (!isEmpty) {
            strcpy(dateRead, dateTemp);
            
            strptime(dateTemp, "%d/%m/%Y", &dataStruct);
            r = mktime(&dataStruct);
            strftime(dateTemp, sizeof(dateTemp), "%d/%m/%Y", &dataStruct); // used only for comparison
            
            if (strcmp(dateTemp, dateRead) == 0 || !previousDate) {
                *resultDate = r;
            } else {
                printf(BOLDRED "Data inválida. Tente novamente.\n" RESET);
            }
            
        } else {
            break;
        }
        
    } while (strcmp(dateRead, "\n") != 0 && (strcmp(dateRead, dateTemp) != 0));
}

/* ReadNumber and edit = ok */
void ReadNumber(int *previousNumber, int *resultNumbers) {
    int validDigit = 0;
    char userInput[5] = {0};
    int isEmpty = 0;
    
    do {
        
        if (previousNumber) {
            printf(BOLDBLACK "\nRead Number[%d]: " RESET, *previousNumber);
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

/* Movie Confirmation */
void MovieConfirmation(struct filme newMovie) {
    time_t r;
    struct tm dateStruct = {0};
    char dateFinal[11] = {0}, dateInitial[11] = {0}, confirm = 0;
    
    strptime(dateInitial, "%d/%m/%Y", &dateStruct);
    r = mktime(&dateStruct);
    
    do {
        strftime(dateFinal, sizeof(dateFinal), "%d/%m/%Y", localtime(&newMovie.dataLancamento));
        
        ClearScreen();
        
        printf(BOLDRED "Confirmação de cadastro:\n" RESET);
        printf(BOLDBLACK "\nNome do filme: \n" RESET);
        printf("%s\n", newMovie.nomeFilme);
        printf(BOLDBLACK "Data de Lançamento: \n" RESET);
        printf("%s\n\n", dateFinal);
        printf(BOLDBLACK "Duração do filme: \n" RESET);
        printf("%d min\n", newMovie.duracaoFilme);
        printf(BOLDRED "\nSalvar(1) ou descartar(2)?\n" RESET);
        printf("-> ");
        scanf("%c", &confirm);
        fseek(stdin, 0, SEEK_END);
        
        switch (confirm) {
            case '1':
                ClearScreen();
                printf(BOLDRED "Filme salvo!\n" RESET);
                AddFilme(newMovie);
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

/* Movie List */
void MovieList() {
    
    /* Variables  */
    struct Array *filmes = GetFilmes();
    
    time_t r;
    struct tm dateStruct = {0};
    char dateFinal[11] = {0}, dateInitial[11] = {0};
    
    r = mktime(&dateStruct);
    strftime(dateInitial, sizeof(dateInitial), "%d/%m/%Y", &dateStruct);
    
    if(filmes == NULL || filmes->count == 0) {
        printf(BOLDRED "\nLISTA VAZIA.\n" RESET);
    } else {
        for (int i = 0; i < filmes->count; i++) {
            strftime(dateFinal, sizeof(dateFinal), "%d/%m/%Y", localtime(&filmes->p[i].dataLancamento));
            
            printf(BOLDRED "\nID: %d)\n" RESET, i + 1);
            printf(BOLDBLACK "Nome do filme: " RESET);
            printf("%s\n", filmes->p[i].nomeFilme);
            printf(BOLDBLACK "Data de lançamento: " RESET);
            printf("%s\n", dateFinal);
            printf(BOLDBLACK "Duração do filme: " RESET);
            printf("%d min\n", filmes->p[i].duracaoFilme);
        }
    }
}
