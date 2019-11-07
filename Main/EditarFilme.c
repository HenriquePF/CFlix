#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "TelaMain.h"
#include "ClearScreen.h"
#include "Filme.h"
#include "TrimFunc.h"
#include "AddMovie.h"
#include "EditMovie.h"
#include "ReadMovie.h"

#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define RESET       "\033[0m"              /* RESET */

void EditarFilme() {
    
    ClearScreen();
    
    struct Array *filmeEdit;
    filmeEdit = GetFilmes();
    int id = 0;
    char option = 0;
    
    printf(BOLDBLACK "***** Editar cadastro de filme - CFLIX *****\n" RESET);
    
    MovieList();
    
    if (filmeEdit == NULL || filmeEdit->count == 0) {
        do{
            
            printf(BOLDBLACK "\n1 - Retornar:\n" RESET);
            printf("-> ");
            scanf("%c", &option);
            fseek(stdin, 0, SEEK_END);
            
            switch (option) {
                case '1':
                    ClearScreen();
                    break;
                    
                default:
                    printf(BOLDRED "Entrada inválida. Tente novamente.\n" RESET);
                    break;
            }
        }while (option != '1');
        
    } else {
        
        do {
            printf(BOLDRED "\nEditar um filme(1) ou Retornar(2):\n" RESET);
            printf("-> ");
            scanf("%c", &option);
            fseek(stdin, 0, SEEK_END);
            
            switch (option) {
                case '1':
                    
                    printf(BOLDBLACK "\nEntre com o ID do filme para editar:\n" RESET);
                    printf("-> ");
                    scanf("%d", &id);
                    fseek(stdin, 0, SEEK_END);

//                    EditMovie(id - 1);
                    ReadMovieName(filmeEdit->p->nomeFilme, filmeEdit->p);
                    ReadMovieDate(&filmeEdit->p->dataLancamento, filmeEdit->p);
                    ReadMovieDuration(&filmeEdit->p->duracaoFilme, filmeEdit->p);
                    MovieList();
                    
                    break;
                    
                case '2':
                    break;
                    
                default:
                    printf(BOLDRED "Entrada inválida. Tente novamente." RESET);
                    break;
            }
        }while(option != '2');
    }
}
