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
    
    /* Variables */
    FILE *filePtr = 0;
    char *filePath = "./EntryBackup.bin";
    filePtr = fopen(filePath, "rb");
    
    printf(BOLDBLACK "***** Catalog - CFLIX *****\n" RESET);
    
    char option = 0;
    
    if (IsEmptyFile(filePtr)) {
        
        printf(BOLDBLACK "\n1 - Return\n2 - Register\n" RESET);
        printf("-> ");
        scanf("%c", &option);
        fseek(stdin, 0, SEEK_END);
        
        do {
            
            switch (option) {
                case '1':
                    break;
                    
                case '2':
                    return EntryRegister();
                    
                default:
                    break;
            }
            
        } while (option != '1');
        
    } else {
        
        RetrieveEntryFile();
        
        do {
            
            printf(BOLDBLACK "\n1 - Return\n2 - Remove\n3 - Edit\n" RESET);
            printf("-> ");
            scanf("%c", &option);
            fseek(stdin, 0, SEEK_END);
            
            switch (option) {
                case '1':
                    break;
                    
                case '2':
                    return ExcludeEntry();
                    
                case '3':
                    EditEntry();
                    
                default:
                    printf(BOLDRED "Invalid option. Try Again.\n" RESET);
                    break;
            }
        } while (option != '1');
    }
}
