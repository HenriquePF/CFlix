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
    
    // Variables
    ClearScreen();
    FILE *filePtr = 0; /* For Reading */
    char *filePath = "./EntryBackup.bin"; /* Current file containing the entries */
    filePtr = fopen(filePath, "rb"); /* Main file will get read - if file doesn't exist, returns NULL */

    int id = 0;
    char option = 0;
    printf(BOLDBLACK "***** Remove Entry - CFLIX *****\n" RESET);
    
    if (IsEmptyFile(filePtr)) {
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
    } else {
        RetrieveEntryFile();
        
        printf(BOLDBLACK "\nEnter the ID to remove the entry:\n" RESET);
        printf("-> ");
        scanf("%d", &id);
        fseek(stdin, 0, SEEK_END);
        
        /* Delete the chosen element */
        DeleteEntryFile(id);
        printf(BOLDRED "Press ENTER to leave.\n" RESET);
        getchar();
    }
    
}
