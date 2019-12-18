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
    char option = 0;
    FILE *getFile = 0;
    
    printf(BOLDBLACK "***** Entry Catalog - CFLIX *****\n" RESET);
    
    getFile = OpenFileBinaryMode();
    
    if (IsEmptyFile(getFile) == 2) {
        printf(BOLDRED "\nFile is empty.\n" RESET);
        CloseFileBinaryMode(getFile);
        
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
    
    } else if (IsEmptyFile(getFile) == 1) {
        printf(BOLDRED "\nFile does not exist.\nA file will be created if you register an entry.\n" RESET);
        CloseFileBinaryMode(getFile);
        
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
        
        GetEntriesFromFile();
        
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
                    return EditEntry();
                    
                default:
                    printf(BOLDRED "Invalid option. Try Again.\n" RESET);
                    break;
            }
        } while (option != '1');
    }
}
