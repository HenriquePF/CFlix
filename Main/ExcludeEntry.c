#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "TelaMain.h"
#include "ClearScreen.h"
#include "Filme.h"
#include "ReadMovie.h"

#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define RESET       "\033[0m"              /* RESET */

void ExcludeEntry() {
    
    ClearScreen();
    
    // Variables
    int id = 0;
    char option = 0;
    FILE *getFile = 0;
    
    printf(BOLDBLACK "***** Remove Entry - CFLIX *****\n" RESET);
    
    getFile = OpenFileBinaryMode();
    if (IsEmptyFile(getFile) == 2) {
        printf(BOLDRED "\nFile is empty.\n" RESET);
        CloseFileBinaryMode(getFile);
        
        do {
            printf(BOLDBLACK "\n1 - Return\n2 - Register\n" RESET);
            printf("-> ");
            scanf("%c", &option);
            fseek(stdin, 0, SEEK_END);
            switch (option) {
                case '1':
                    break;
                    
                case '2':
                    return EntryRegister();
                    
                default:
                    printf(BOLDRED "Invalid option.\n" RESET);
                    break;
            }
        } while (option != '1');
    } else if (IsEmptyFile(getFile) == 1) {
        printf(BOLDRED "\nFile does not exist.\nA file will be created if you register an entry.\n" RESET);
        
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
        
        printf(BOLDBLACK "\nEnter the ID to remove the entry:\n" RESET);
        printf(BOLDBLACK "-> " RESET);
        scanf("%d", &id);
        fseek(stdin, 0, SEEK_END);
        
        /* Delete the chosen element */
        DeleteBinaryData(id);
        
        do {
            
            printf(BOLDBLACK "\n1 - Return\n2 - Delete\n" RESET);
            printf(BOLDBLACK "-> " RESET);
            scanf("%c", &option);
            fseek(stdin, 0, SEEK_END);
            
            switch (option) {
                case '1':
                    break;
                    
                case '2':
                    return ExcludeEntry();
                    
                default:
                    printf(BOLDRED "Invalid input. Try again.\n" RESET);
                    break;
            }
            
        } while (option != '1');
    }
    
}
