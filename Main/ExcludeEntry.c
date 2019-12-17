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
    int id = 0;
    
    printf(BOLDBLACK "***** Excluir filme - CFLIX *****\n" RESET);
    
    /* Retrieve elements from the bin file */
    RetrieveEntryFile();
    
    printf(BOLDBLACK "\nEntre com o ID para deletar o filme:\n" RESET);
    printf("-> ");
    scanf("%d", &id);
    fseek(stdin, 0, SEEK_END);

    /* Delete the chosen element */
    DeleteEntryFile(id);

}
