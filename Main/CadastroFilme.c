#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "TelaMain.h"
#include "ClearScreen.h"
#include "Filme.h"
#include "TrimFunc.h"
#include "ReadMovie.h"

#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define RESET       "\033[0m"              /* RESET */

void CadastrarFilme(void) {
    ClearScreen();
    
    /*  Variables */
    struct filme novoFilme = {0};
    
    char *nome = novoFilme.nomeFilme;
    time_t *data = &novoFilme.dataLancamento;
    int *num = &novoFilme.duracaoFilme;
    
    char option = 0;
    
    printf(BOLDBLACK "***** Cadastro de flmes - CFLIX *****\n" RESET);
    
    /* Movie Name Function */
//    ReadMovieName(NULL, &novoFilme);
    ReadText(NULL, &nome);
    
    /* Movie date Function */
//    ReadMovieDate(NULL, &novoFilme);
    ReadDate(NULL, data);
    
    /* Movie duration Function */
//    ReadMovieDuration(NULL, &novoFilme);
    ReadNumber(NULL, num);    
    
    /* Movie confirmation Function */
    MovieConfirmation(novoFilme);
    
    /* Menu */
    do{
        printf(BOLDBLACK "\n1 - Retornar:\n2 - Adicionar:\n" RESET);
        printf("-> ");
        scanf("%c", &option);
        fseek(stdin, 0, SEEK_END);
        
        switch (option) {
            case '1':
                break;
                
            case '2':
                return CadastrarFilme();
                
            default:
                printf(BOLDRED "Entrada inválida. Tente novamente." RESET);
                break;
        }
    } while(option != '1');
}
