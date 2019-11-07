#include <stdlib.h>
#include <string.h>
#include "ReadMovie.h"
#include "Filme.h"
#include "ClearScreen.h"
#include "TrimFunc.h"

#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define RESET       "\033[0m"              /* RESET */

void EditMovie(int index) {
    
    /* Variables */
    struct Array *filmeEdit = GetFilmes();
    struct filme *f = {0};
    f = &(filmeEdit->p[index - 1]);
    
    ReadMovieName(f->nomeFilme, f);
    ReadMovieDate(&f->dataLancamento, f);
    ReadMovieDuration(&f->duracaoFilme, f);
}

void ReadMovieName(char *prevName, struct filme *movie) {
    char movieName[199], *newString;
    
    if (prevName == NULL) {
        do{
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
        
        do{
            printf(BOLDBLACK "\nNome do filme [%s]: " RESET, movie->nomeFilme);
            fgets(movieName, sizeof(movieName), stdin);
            
            if (strcmp(movieName, "\n") != 0) {
                
                newString = StringTrimmer(movieName);
                TrimTrailing(newString);
                
                strcpy(movie->nomeFilme, newString);
                
                printf("Nome: %s\n", movie->nomeFilme);
            }
        } while((strcmp(movieName, "\n") != 0) && (strcmp(movieName, "\n") == 0));
    }
}

void ReadMovieDate(long *prevDate, struct filme *movie) {
    char dataInicial[11], dataComp[11];
    struct tm dataStrct = {0};
    int comp = 0;
    time_t r;
    
    if (prevDate == 0) {
        do{
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
        } while((comp = strcmp(dataInicial, dataComp)) != 0);
        
    } else {
        
        struct tm dataStrct = {0};
        time_t r, data = 0;
        struct tm ts = {0};
        
        int comp = 0;
        char dataFinal[11], dataInicial[11], dataComp[11];
        
        data = movie->dataLancamento;
        ts = *localtime(&data);
        strftime(dataFinal, sizeof(dataFinal), "%d/%m/%Y", localtime(&movie->dataLancamento));
        
        do{
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
        }while((comp = strcmp(dataInicial, dataComp)) != 0);
    }
}

void ReadMovieDuration(int *prevDuration, struct filme *movie) {
    int validDigit = 0;
    char duracao[5];
    int duracaoValid = 0;
    
    if (prevDuration == 0) {
        
        do{
            printf(BOLDBLACK "Duração em minutos:\n" RESET);
            printf("-> ");
            validDigit = scanf("%d", &duracaoValid);
            fseek(stdin, 0, SEEK_END);
            int temp = 0;
            while(validDigit != 1){
                while((temp=getchar()) != EOF && temp != '\n');
                printf(BOLDRED "Entrada inválida. Tente novamente.\n" RESET);
                validDigit = scanf("%d", &duracaoValid);
            }
            
            movie->duracaoFilme = duracaoValid;
            ClearScreen();
        }while(validDigit != 1);
        
    } else {
        
        /* Duration Edition Segment */
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
        } while(duracao[0] == '\n');
    }
}


/* Movie Confirmation */
void MovieConfirmation(struct filme novoFilme) {
    time_t r;
    struct tm dataStrct = {0};
    char dataFinal[11], dataInicial[11], confirm = 0;
    
    strptime(dataInicial, "%d/%m/%Y", &dataStrct);
    r = mktime(&dataStrct);
    
    do{
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
    }while(confirm != '1' && confirm != '2');
}

/* Movie List */
void MovieList() {
    
    /* Variables  */
    struct Array *filmes = GetFilmes();
    
    time_t r;
    struct tm dataStrct = {0};
    char dataFinal[11], dataInicial[11];
    
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
