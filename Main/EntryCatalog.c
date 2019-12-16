#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "TelaMain.h"
#include "ClearScreen.h"
#include "Filme.h"
#include "ReadMovie.h"

#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define RESET       "\033[0m"              /* RESET */

void EntryCatalog(void) {
    ClearScreen();
    
    FILE *filePtr = 0;
    char *filePath = "./EntryBackup.bin";
    
    filePtr = fopen(filePath, "ab");
    
    printf(BOLDBLACK "***** Catálogo - CFLIX *****\n" RESET);
    
    char option = 0;
    unsigned long sz = 0;

    RetrieveEntryFile(); // Check it IS or IS NOT empty....
    
    if (sz == 0) {
        printf(BOLDRED "\nArquivo vazio.\n" RESET);
        rewind(filePtr);
        
        do {
            printf(BOLDBLACK "\n1 - Retornar:\n2 - Cadastrar:\n" RESET);
            printf("-> ");
            scanf("%c", &option);
            fseek(stdin, 0, SEEK_END);
            
            switch (option) {
                    
                case '1':
                    break;
                    
                case '2':
                    return EntryRegister();
                    
                default:
                    printf(BOLDRED "\nOpção inválida. Tente novamente.\n" RESET);
                    break;
            }
            
        } while (option != '1');
    }
}
