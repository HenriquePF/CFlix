#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "EntryCatalog.h"
#include "CadastroFilme.h"
#include "EditEntry.h"
#include "ExcludeEntry.h"
#include "ClearScreen.h"
#include "Filme.h"
#include "ReadMovie.h"

#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define RESET       "\033[0m"              /* RESET */

int main(void) {
    
    char option = 0;
    
    
    do {
        ClearScreen();
        printf(BOLDBLACK "***** CFLIX *****\n\n" RESET);

        printf(BOLDBLACK "1) Listar catálogo.\n" RESET);
        printf(BOLDBLACK "2) Cadastrar filme.\n" RESET);
        printf(BOLDBLACK "3) Editar filme.\n" RESET);
        printf(BOLDBLACK "4) Excluir filme.\n" RESET);
        printf(BOLDBLACK "5) Sair.\n\n" RESET);
        
        printf(BOLDBLACK "Entre com a opção desejada:\n" RESET);
        printf("-> ");
        scanf("%c", &option);
        fseek(stdin, 0, SEEK_END);
        
        switch (option) {
            case '1':
                EntryCatalog();
                break;
                
            case '2':
                EntryRegister();
                break;
                
            case '3':
                EditEntry();
                break;
                
            case '4':
                ExcludeEntry();
                break;
                
            case '5':
                printf(BOLDRED "\n\nSaindo..." RESET);
                break;
                
            default:
                break;
        }
        fseek(stdin, 0, SEEK_END);
        
    } while (option != '5');
    
    return 0;
}
