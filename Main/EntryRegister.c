#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "TelaMain.h"
#include "ClearScreen.h"
#include "Filme.h"
#include "TrimFunc.h"
#include "ReadMovie.h"

#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define RESET       "\033[0m"              /* RESET */

void EntryRegister(void) {
    ClearScreen();
    
    /*  Variables */
    struct filme newEntry = {0};
    
    int *id = &newEntry.entryId;
    char *name = newEntry.nomeFilme;
    time_t *date = &newEntry.dataLancamento;
    int *num = &newEntry.duracaoFilme;
    
    char option = 0;
    
    printf(BOLDBLACK "***** Entry Register - CFLIX *****\n" RESET);
    
    /* Read Text Function */
    ReadNumber(NULL, id, "id");
    
    while (FindEntryById(*id) != -1) {
        printf("Id already exists\n");
        ReadNumber(NULL, id, "id");
    }
    
    /* Read Text Function */
    ReadText(NULL, name);
    
    /* Read Date Function */
    ReadDate(NULL, date);
    
    /* Read Number Function */
    ReadNumber(NULL, num, "duration");
    
    /* Movie/Entry Confirmation Function */
    EntryConfirmation(newEntry);
    
    /* Menu */
    do{
        printf(BOLDBLACK "\n1 - Return:\n2 - Register:\n" RESET);
        printf("-> ");
        scanf("%c", &option);
        fseek(stdin, 0, SEEK_END);
        
        switch (option) {
            case '1':
                break;
                
            case '2':
                return EntryRegister();
                
            default:
                printf(BOLDRED "Invalid option. Try again." RESET);
                break;
        }
    } while (option != '1');
}
