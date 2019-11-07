#include "EditMovie.h"
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include "Filme.h"
#include "TrimFunc.h"

#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define RESET       "\033[0m"              /* RESET */

/* Name Edit */
void EditarNome() {
    
}

/* Date Edit */
void EditarData() {
    
}

/* Duration Edit */
void EditarDuracao() {
    
}

void EditMovie(int index) {
    
    /* Variables */
    struct Array *filmeEdit = GetFilmes();
    
    struct filme *f = {0};
    
    /* Usar f */
    f = &(filmeEdit->p[index]);
    
    struct tm dataStrct = {0};
    time_t r, data = 0;
    struct tm ts = {0};
    
    int comp = 0;
    char movieName[199], *newString, dataFinal[11], dataInicial[11], dataComp[11], duracao[5];
    
    data = f->dataLancamento;
    ts = *localtime(&data);
    strftime(dataFinal, sizeof(dataFinal), "%d/%m/%Y", localtime(&f->dataLancamento));
    /* ---//--- */
    
    /* Name Edition Segment  */
    do{
        printf(BOLDBLACK "\nNome do filme [%s]: " RESET, f->nomeFilme);
        fgets(movieName, sizeof(movieName), stdin);
        
        if (strcmp(movieName, "\n") != 0) {
            
            newString = StringTrimmer(movieName);
            TrimTrailing(newString);
            
            strcpy(f->nomeFilme, newString);
            
            printf("Nome: %s\n", f->nomeFilme);
        }
    } while((strcmp(movieName, "\n") != 0) && (strcmp(movieName, "\n") == 0));
    /* ---//--- */
    
    /* Date Edition Segment */
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
            
            f->dataLancamento = r;
            fseek(stdin, 0, SEEK_END);
            printf("Nome: %ld\n", f->dataLancamento);
        } else {
            break;
        }
    }while((comp = strcmp(dataInicial, dataComp)) != 0);
    /* ---//--- */
    
    /* Duration Edition Segment */
    do {
        printf(BOLDBLACK "\nDuração[%d]: " RESET, f->duracaoFilme);
        fgets(duracao, sizeof(duracao), stdin);
        
        if (duracao[0] != '\n') {
            duracao[strlen(duracao) - 1] = 0;
            int j = atoi(duracao);
            
            f->duracaoFilme = j;
            printf("Nome: %d\n", f->duracaoFilme);
        } else {
            break;
        }
    } while(duracao[0] == '\n');
}
/* ---//--- */
