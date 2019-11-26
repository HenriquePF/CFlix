#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "TelaMain.h"
#include "ClearScreen.h"
#include "Filme.h"

#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define RESET       "\033[0m"              /* RESET */

void CatalogoLista(void) {
    ClearScreen();
    
    char option = 0;
    struct Array *filmes = GetFilmes();
    
    printf(BOLDBLACK "***** Catálogo - CFLIX *****\n" RESET);
    
    MovieList();
    
    if(filmes == NULL || filmes->count == 0) {
        do {
            printf( BOLDBLACK"\n1 - Retornar:\n2 - Cadastrar:\n" RESET);
            printf("-> ");
            scanf("%c", &option);
            fseek(stdin, 0, SEEK_END);
            
            switch (option) {
                case '1':
                    break;
                    
                case '2':
                    return CadastrarFilme();
                    break;
                    
                default:
                    printf(BOLDRED "Entrada inválida. Tente novamente.\n" RESET);
                    break;
            }
        } while (option != '1');
        
    } else {
        
        do {
            printf( BOLDBLACK"\n1 - Retornar:\n2 - Editar\n3 - Deletar\n" RESET);
            printf("-> ");
            scanf("%c", &option);
            fseek(stdin, 0, SEEK_END);
            
            switch (option) {
                case '1':
                    ClearScreen();
                    break;
                    
                case '2':
                    return EditarFilme();
                    
                case '3':
                    return ExcluirFilme();
                    
                default:
                    printf(BOLDRED "Entrada inválida. Tente novamente.\n" RESET);
                    break;
            }
        } while (option != '1');
    }
}
