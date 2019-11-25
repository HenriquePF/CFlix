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
    struct Array *filmeEdit = GetFilmes();
    struct filme *f = {0};
    f = &((filmeEdit->p[index - 1]));
    
    char *nomeEditado = f->nomeFilme;
    time_t *dataEditada = &f->dataLancamento;
    int *numEditado = &f->duracaoFilme;
    
    ReadText(f->nomeFilme, nomeEditado);
    ReadDate(&f->dataLancamento, dataEditada);
    ReadNumber(&f->duracaoFilme, numEditado);
}

// ReadText and edit = ok;
void ReadText(char *previousText, char *resultText) {
    char movieName[199] = {0}, *newString;
    
    do {
        if (previousText) {
            printf(BOLDBLACK "\nRead Text [%s]: " RESET, previousText);
        } else {
            printf(BOLDBLACK "\nRead Text:\n" RESET);
            printf("-> ");
        }
        
        fgets(movieName, sizeof(movieName), stdin);
        
        newString = StringTrimmer(movieName);
        TrimTrailing(newString);
        
        if (!previousText && !strcmp(movieName, "\n")) {
            printf(BOLDRED "Nome inválido. Tente novamente.\n" RESET);
        }
        
        if (strcmp(movieName, "\n") != 0) {
            strcpy(resultText, newString);
        }
        
        free(newString);
        newString = NULL;
    } while (previousText == NULL && strcmp(movieName, "\n") == 0);
}

// ReadDate and edit = ok;
void ReadDate(time_t *previousDate, time_t *resultDate) {
    char dataFinal[11] = {0}, dataInicial[11] = {0}, dataComp[11] = {0};
    
    do {
        struct tm dataStrct = {0};
        time_t r = 0;
        struct tm ts = {0};
        
        if (previousDate) {
            ts = *localtime(previousDate);
            strftime(dataFinal, sizeof(dataFinal), "%d/%m/%Y", localtime(previousDate));
            printf(BOLDBLACK "\nRead Date[%s]: " RESET, dataFinal);
        } else {
            printf(BOLDBLACK "Read Date\n" RESET);
            printf("-> ");
        }
        
        fgets(dataInicial, 11, stdin);
        fseek(stdin, 0, SEEK_END);
        
        if (strcmp(dataInicial, "\n") != 0) {
            strcpy(dataComp, dataInicial);
            
            strptime(dataInicial, "%d/%m/%Y", &dataStrct);
            r = mktime(&dataStrct);
            strftime(dataInicial, sizeof(dataInicial), "%d/%m/%Y", &dataStrct); // used only for comparison
            
            if (strcmp(dataInicial, dataComp) == 0) {
                *resultDate = r;
            } else {
                printf(BOLDRED "Data inválida. Tente novamente.\n" RESET);
            }
        } else {
            printf(BOLDRED "Data inválida. Tente novamente.\n" RESET);
        }
        
        
    } while (strcmp(dataInicial, "\n") != 0 && (strcmp(dataInicial, dataComp) != 0));
}

// ReadNumber and edit = ok;
void ReadNumber(int *previousNumber, int *resultNumbers) {
    int validDigit = 0;
    char duracao[5] = {0};
    
    do {
        if (previousNumber) {
            printf(BOLDBLACK "\nRead Number[%d]: " RESET, *previousNumber);
        } else {
            printf(BOLDBLACK "Read Number:\n" RESET);
        }
        
        fgets(duracao, sizeof(duracao), stdin);
        validDigit = atoi(duracao);
        if (!validDigit) {
            printf(BOLDRED "Número inválido. Tente novamente." RESET);
        } else {
            *resultNumbers = validDigit;
        }
        
        // USE A FOR LOOP TO CHECK INPUT!
        
    } while (validDigit);
    
}

/* Add/Edit Movie Name */
void ReadMovieName(char *prevName, struct filme *movie) {
    
    char movieName[199] = {0}, *newString;
    
    if (prevName == NULL) {
        do {
            printf(BOLDBLACK "\nNome do filme:\n" RESET);
            printf("-> ");
            fgets(movieName, sizeof(movieName), stdin);
            
            newString = StringTrimmer(movieName);
            TrimTrailing(newString);
            
            if (movieName[0] == '\n' || movieName[0] == ' ') {
                printf(BOLDRED "Nome inválido. Tente novamente.\n" RESET);
            }
            
            strcpy(movie->nomeFilme, newString);
        } while(movieName[0] == '\n' || movieName[0] == ' ');
        
    } else {
        
        do {
            printf(BOLDBLACK "\nNome do filme [%s]: " RESET, movie->nomeFilme);
            fgets(movieName, sizeof(movieName), stdin);
            
            if (strcmp(movieName, "\n") != 0) {
                
                newString = StringTrimmer(movieName);
                TrimTrailing(newString);
                strcpy(movie->nomeFilme, newString);
                
            }
        } while ((strcmp(movieName, "\n") != 0) && (strcmp(movieName, "\n") == 0));
    }
}

/* Add/Edit Movie Date */
void ReadMovieDate(long *prevDate, struct filme *movie) {
    char dataInicial[11] = {0}, dataComp[11] = {0};
    struct tm dataStrct = {0};
    int comp = 0;
    time_t r;
    
    if (prevDate == NULL) {
        do {
            printf(BOLDBLACK "Data de lançamento:(dd/mm/yyyy)\n" RESET);
            printf("-> ");
            fgets(dataInicial, 11, stdin);
            
            if (!(strchr(dataInicial, '\n'))) {
                while (fgetc(stdin) != '\n');
            }
            
            strcpy(dataComp, dataInicial);
            
            strptime(dataInicial, "%d/%m/%Y", &dataStrct);
            r = mktime(&dataStrct);
            strftime(dataInicial, sizeof(dataInicial), "%d/%m/%Y", &dataStrct);
            
            if ((comp = strcmp(dataInicial, dataComp)) != 0) {
                printf(BOLDRED "Data inválida. Tente novamente.\n" RESET);
            }
            
            movie->dataLancamento = r;
        } while ((comp = strcmp(dataInicial, dataComp)) != 0);
        
    } else {
        
        struct tm dataStrct = {0};
        time_t r, data = 0;
        struct tm ts = {0};
        
        int comp = 0;
        char dataFinal[11], dataInicial[11], dataComp[11];
        
        data = movie->dataLancamento;
        ts = *localtime(&data);
        strftime(dataFinal, sizeof(dataFinal), "%d/%m/%Y", localtime(&data));
        
        do {
            printf(BOLDBLACK "\nData de lançamento[%s]: " RESET, dataFinal);
            fgets(dataInicial, 11, stdin);
            
            if (strcmp(dataInicial, "\n") != 0) {
                strcpy(dataComp, dataInicial);
                
                strptime(dataInicial, "%d/%m/%Y", &dataStrct);
                r = mktime(&dataStrct);
                strftime(dataInicial, sizeof(dataInicial), "%d/%m/%Y", &dataStrct);
                
                if ((comp = strcmp(dataInicial, dataComp)) != 0) {
                    printf(BOLDRED "Data inválida. Tente novamente.\n" RESET);
                }
                
                movie->dataLancamento = r;
                fseek(stdin, 0, SEEK_END);
            } else {
                break;
            }
        } while ((comp = strcmp(dataInicial, dataComp)) != 0);
    }
}

/* Add/Edit Movie Duration */
void ReadMovieDuration(int *prevDuration, struct filme *movie) {
    int validDigit = 0;
    char duracao[5] = {0};
    int duracaoValid = 0;
    
    if (prevDuration == NULL) {
        
        do {
            printf(BOLDBLACK "Duração em minutos:\n" RESET);
            printf("-> ");
            validDigit = scanf("%d", &duracaoValid);
            fseek(stdin, 0, SEEK_END);
            int temp = 0;
            while(validDigit != 1){
                while((temp=getchar()) != EOF && temp != '\n');
                validDigit = scanf("%d", &duracaoValid);
            }
            
            movie->duracaoFilme = duracaoValid;
            ClearScreen();
        }while(validDigit != 1);
        
    } else {
        
        do {
            printf(BOLDBLACK "\nDuração[%d]: " RESET, movie->duracaoFilme);
            fgets(duracao, sizeof(duracao), stdin);
            
            if (duracao[0] != '\n') {
                duracao[strlen(duracao) - 1] = 0;
                int j = atoi(duracao);
                
                movie->duracaoFilme = j;
            } else {
                break;
            }
        } while (duracao[0] == '\n');
    }
}

/* Add/Edit Movie Confirmation */
void MovieConfirmation(struct filme novoFilme) {
    time_t r;
    struct tm dataStrct = {0};
    char dataFinal[11] = {0}, dataInicial[11] = {0}, confirm = 0;
    
    strptime(dataInicial, "%d/%m/%Y", &dataStrct);
    r = mktime(&dataStrct);
    
    do {
        strftime(dataFinal, sizeof(dataFinal), "%d/%m/%Y", localtime(&novoFilme.dataLancamento));
        
        ClearScreen();
        
        printf(BOLDRED "Confirmação de cadastro:\n" RESET);
        printf(BOLDBLACK "\nNome do filme: \n" RESET);
        printf("%s\n\n", novoFilme.nomeFilme);
        printf(BOLDBLACK "Data de Lançamento: \n" RESET);
        printf("%s\n\n", dataFinal);
        printf(BOLDBLACK "Duração do filme: \n" RESET);
        printf("%d min\n", novoFilme.duracaoFilme);
        printf(BOLDRED "\nSalvar(1) ou descartar(2)?\n" RESET);
        printf("-> ");
        scanf("%c", &confirm);
        fseek(stdin, 0, SEEK_END);
        
        switch (confirm) {
            case '1':
                ClearScreen();
                printf(BOLDRED "Filme salvo!\n" RESET);
                AddFilme(novoFilme);
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
    struct tm dataStrct = {0};
    char dataFinal[11] = {0}, dataInicial[11] = {0};
    
    r = mktime(&dataStrct);
    strftime(dataInicial, sizeof(dataInicial), "%d/%m/%Y", &dataStrct);
    
    if(filmes == NULL || filmes->count == 0) {
        printf(BOLDRED "\nLISTA VAZIA.\n" RESET);
    } else {
        for (int i = 0; i < filmes->count; i++) {
            strftime(dataFinal, sizeof(dataFinal), "%d/%m/%Y", localtime(&filmes->p[i].dataLancamento));
            
            printf(BOLDRED "\nID: %d)\n" RESET, i + 1);
            printf(BOLDBLACK "Nome do filme: " RESET);
            printf("%s\n", filmes->p[i].nomeFilme);
            printf(BOLDBLACK "Data de lançamento: " RESET);
            printf("%s\n", dataFinal);
            printf(BOLDBLACK "Duração do filme: " RESET);
            printf("%d min\n", filmes->p[i].duracaoFilme);
        }
    }
}
