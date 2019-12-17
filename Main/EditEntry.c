#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "TelaMain.h"
#include "ClearScreen.h"
#include "Filme.h"
#include "TrimFunc.h"
#include "ReadMovie.h"

#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define RESET       "\033[0m"              /* RESET */

void EditEntry() { // Check it IS or IS NOT empty....
    
    ClearScreen();
    
    /* Variables */
    FILE *filePtr = 0;
    char *filePath = "./EntryBackup.bin";
    char option = 0;
    int id = 0;
    filePtr = fopen(filePath, "rb");
    
    printf(BOLDBLACK "***** Edit Entry - CFLIX *****\n" RESET);
    
    if (IsEmptyFile(filePtr) == 1) {
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
    
        printf(BOLDBLACK "\nEnter the entry's ID to edit:\n" RESET);
        printf("-> ");
        scanf("%d", &id);
        fseek(stdin, 0, SEEK_END);
    
        EditBinData(id);
        
    }
}
