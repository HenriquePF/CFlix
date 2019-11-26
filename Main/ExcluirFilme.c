#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "TelaMain.h"
#include "ClearScreen.h"
#include "Filme.h"

#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define RESET       "\033[0m"              /* RESET */

void ExcluirFilme() {
    
    // Variables
    ClearScreen();
    char option = 0, delOption = 0;
    int index = 0;
    struct Array *filmes = GetFilmes();
    
    printf(BOLDBLACK "***** Excluir filme - CFLIX *****\n" RESET);
    
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
            
        } while(option != '1');
        
    } else {
        
        do {
            printf(BOLDBLACK "\nExcluir(1) ou não(2)?\n" RESET);
            printf("-> ");
            scanf("%c", &delOption);
            fseek(stdin, 0, SEEK_END);
            
            switch (delOption) {
                case '1':
                    printf(BOLDBLACK "\nEntre com o ID para deletar o filme:\n" RESET);
                    printf("-> ");
                    scanf("%d", &index);
                    fseek(stdin, 0, SEEK_END);
                    
                    DeleteFilme(filmes, index - 1);
                    
                case '2':
                    break;
                    
                default:
                    printf(BOLDRED "Opção inválida. Tente novamente.\n" RESET);
                    break;
            }
            
        } while (delOption != '1' && delOption != '2');
        
        do {
            printf(BOLDBLACK "\n1 - Menu:\n2 - Catalogo:\n" RESET);
            printf("-> ");
            scanf("%c", &option);
            fseek(stdin, 0, SEEK_END);
            
            switch (option) {
                case '1':
                    break;
                    
                case '2':
                    return CatalogoLista();
                    
                default:
                    printf(BOLDRED "Entrada inválida. Tente novamente.\n" RESET);
                    break;
            }
        } while (option != '1');
    }
}
