#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "TelaMain.h"
#include "ClearScreen.h"
#include "Filme.h"
#include "TrimFunc.h"
<<<<<<< HEAD
=======
#include "AddMovie.h"
>>>>>>> 273ee77a5cfdc30de593f8191f8d4900e92564c4
#include "ReadMovie.h"

#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define RESET       "\033[0m"              /* RESET */

void CadastrarFilme(void) {
    ClearScreen();
    
    // Variables
    struct filme novoFilme = {0};
<<<<<<< HEAD
    char option = 0;    
=======
    char option = 0;
>>>>>>> 273ee77a5cfdc30de593f8191f8d4900e92564c4
    
    printf(BOLDBLACK "***** Cadastro de flmes - CFLIX *****\n" RESET);
    
    // Movie Name Function
<<<<<<< HEAD
    ReadMovieName(NULL, &novoFilme);
    
    // Movie date Function
    ReadMovieDate(NULL, &novoFilme);
    
    // Movie duration Function
=======
//    AddMovieName(novoFilme);
    ReadMovieName(NULL, &novoFilme);
    
    // Movie date Function
//    AddMovieRelease(novoFilme);
    ReadMovieDate(NULL, &novoFilme);
    
    // Movie duration Function
//    AddMovieDuration(novoFilme);
>>>>>>> 273ee77a5cfdc30de593f8191f8d4900e92564c4
    ReadMovieDuration(NULL, &novoFilme);
    
    // Movie confirmation Function
    MovieConfirmation(novoFilme);
    
    //Menu
    do{
        printf(BOLDBLACK "\n1 - Retornar:\n2 - Adicionar:\n" RESET);
        printf("-> ");
        scanf("%c", &option);
        fseek(stdin, 0, SEEK_END);
        
        switch (option) {
            case '1':
                break;
                
            case '2':
                return CadastrarFilme();
                
            default:
                printf(BOLDRED "Entrada inválida. Tente novamente." RESET);
                break;
        }
    } while(option != '1');
}
