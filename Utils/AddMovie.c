#include <stdio.h>
#include <string.h>
#include "Filme.h"
#include "TrimFunc.h"
#include "ClearScreen.h"

#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define RESET       "\033[0m"              /* RESET */


/* Add Movie Name */
<<<<<<< HEAD
//void AddMovieName(struct filme novoFilme) {
//    char movieName[199], *newString;
//
//    do{
//        printf(BOLDBLACK "\nNome do filme:\n" RESET);
//        printf("-> ");
//        fgets(movieName, sizeof(movieName), stdin);
//
//        newString = StringTrimmer(movieName);
//        TrimTrailing(newString);
//
//        if (movieName[0] == '\n' || movieName[0] == ' ') {
//            printf(BOLDRED "Nome inválido. Tente novamente.\n" RESET);
//        }
//
//        strcpy(novoFilme.nomeFilme, newString);
//    } while(movieName[0] == '\n' || movieName[0] == ' ');
//}
//
///* Add Movie Release Date */
//void AddMovieRelease(struct filme novoFilme) {
//    char dataInicial[11], dataComp[11];
//    struct tm dataStrct = {0};
//    int comp = 0;
//    time_t r;
//
//    do{
//        printf(BOLDBLACK "Data de lançamento:(dd/mm/yyyy)\n" RESET);
//        printf("-> ");
//        fgets(dataInicial, 11, stdin);
//
//        if (!(strchr(dataInicial, '\n'))) {
//            while (fgetc(stdin) != '\n');
//        }
//
//        strcpy(dataComp, dataInicial);
//
//        strptime(dataInicial, "%d/%m/%Y", &dataStrct);
//        r = mktime(&dataStrct);
//        strftime(dataInicial, sizeof(dataInicial), "%d/%m/%Y", &dataStrct);
//
//        if ((comp = strcmp(dataInicial, dataComp)) != 0) {
//            printf(BOLDRED "Data inválida. Tente novamente.\n" RESET);
//        }
//
//        novoFilme.dataLancamento = r;
//    } while((comp = strcmp(dataInicial, dataComp)) != 0);
//}
//
///* Add Movie Duration */
//void AddMovieDuration(struct filme novoFilme) {
//    int duracao = 0, validDigit = 0;
//
//    do{
//        printf(BOLDBLACK "Duração em minutos:\n" RESET);
//        printf("-> ");
//        validDigit = scanf("%d", &duracao);
//        fseek(stdin, 0, SEEK_END);
//        int temp = 0;
//        while(validDigit != 1){
//            while((temp=getchar()) != EOF && temp != '\n');
//            printf(BOLDRED "Entrada inválida. Tente novamente.\n" RESET);
//            validDigit = scanf("%d", &duracao);
//        }
//
//        novoFilme.duracaoFilme = duracao;
//        ClearScreen();
//    }while(validDigit != 1);
//}
//
///* Movie Confirmation */
//void MovieConfirmation(struct filme novoFilme) {
//    time_t r;
//    struct tm dataStrct = {0};
//    char dataFinal[11], dataInicial[11], confirm = 0;
//
//    strptime(dataInicial, "%d/%m/%Y", &dataStrct);
//    r = mktime(&dataStrct);
//
//    do{
//        strftime(dataFinal, sizeof(dataFinal), "%d/%m/%Y", localtime(&novoFilme.dataLancamento));
//
//        ClearScreen();
//
//        printf(BOLDRED "Confirmação de cadastro:\n" RESET);
//        printf(BOLDBLACK "\nNome do filme: \n" RESET);
//        printf("%s\n\n", novoFilme.nomeFilme);
//        printf(BOLDBLACK "Data de Lançamento: \n" RESET);
//        printf("%s\n\n", dataFinal);
//        printf(BOLDBLACK "Duração do filme: \n" RESET);
//        printf("%d min\n", novoFilme.duracaoFilme);
//        printf(BOLDRED "\nSalvar(1) ou descartar(2)?\n" RESET);
//        printf("-> ");
//        scanf("%c", &confirm);
//        fseek(stdin, 0, SEEK_END);
//
//        switch (confirm) {
//            case '1':
//                ClearScreen();
//                printf(BOLDRED "Filme salvo!\n" RESET);
//                AddFilme(novoFilme);
//                break;
//
//            case '2':
//                ClearScreen();
//                printf(BOLDRED "\nFilme não salvo.\n" RESET);
//                break;
//
//            default:
//                break;
//        }
//    }while(confirm != '1' && confirm != '2');
//}
//
///* Movie List */
//void MovieList() {
//
//    /* Variables  */
//    struct Array *filmes = GetFilmes();
//
//    time_t r;
//    struct tm dataStrct = {0};
//    char dataFinal[11], dataInicial[11];
//
//    r = mktime(&dataStrct);
//    strftime(dataInicial, sizeof(dataInicial), "%d/%m/%Y", &dataStrct);
//
//    if(filmes == NULL || filmes->count == 0) {
//        printf(BOLDRED "\nLISTA VAZIA.\n" RESET);
//    } else {
//        for (int i = 0; i < filmes->count; i++) {
//            strftime(dataFinal, sizeof(dataFinal), "%d/%m/%Y", localtime(&filmes->p[i].dataLancamento));
//
//            printf(BOLDRED "\nID: %d)\n" RESET, i + 1);
//            printf(BOLDBLACK "Nome do filme: " RESET);
//            printf("%s\n", filmes->p[i].nomeFilme);
//            printf(BOLDBLACK "Data de lançamento: " RESET);
//            printf("%s\n", dataFinal);
//            printf(BOLDBLACK "Duração do filme: " RESET);
//            printf("%d min\n", filmes->p[i].duracaoFilme);
//        }
//    }
//}
=======
void AddMovieName(struct filme novoFilme) {
    char movieName[199], *newString;
    
    do{
        printf(BOLDBLACK "\nNome do filme:\n" RESET);
        printf("-> ");
        fgets(movieName, sizeof(movieName), stdin);
        
        newString = StringTrimmer(movieName);
        TrimTrailing(newString);
        
        if (movieName[0] == '\n' || movieName[0] == ' ') {
            printf(BOLDRED "Nome inválido. Tente novamente.\n" RESET);
        }
        
        strcpy(novoFilme.nomeFilme, newString);
    } while(movieName[0] == '\n' || movieName[0] == ' ');
}

/* Add Movie Release Date */
void AddMovieRelease(struct filme novoFilme) {
    char dataInicial[11], dataComp[11];
    struct tm dataStrct = {0};
    int comp = 0;
    time_t r;
    
    do{
        printf(BOLDBLACK "Data de lançamento:(dd/mm/yyyy)\n" RESET);
        printf("-> ");
        fgets(dataInicial, 11, stdin);
        
        if (!(strchr(dataInicial, '\n'))) {
            while (fgetc(stdin) != '\n');
        }
        
        strcpy(dataComp, dataInicial);
        
        strptime(dataInicial, "%d/%m/%Y", &dataStrct);
        r = mktime(&dataStrct);
        strftime(dataInicial, sizeof(dataInicial), "%d/%m/%Y", &dataStrct);
        
        if ((comp = strcmp(dataInicial, dataComp)) != 0) {
            printf(BOLDRED "Data inválida. Tente novamente.\n" RESET);
        }
        
        novoFilme.dataLancamento = r;
    } while((comp = strcmp(dataInicial, dataComp)) != 0);
}

/* Add Movie Duration */
void AddMovieDuration(struct filme novoFilme) {
    int duracao = 0, validDigit = 0;
    
    do{
        printf(BOLDBLACK "Duração em minutos:\n" RESET);
        printf("-> ");
        validDigit = scanf("%d", &duracao);
        fseek(stdin, 0, SEEK_END);
        int temp = 0;
        while(validDigit != 1){
            while((temp=getchar()) != EOF && temp != '\n');
            printf(BOLDRED "Entrada inválida. Tente novamente.\n" RESET);
            validDigit = scanf("%d", &duracao);
        }
        
        novoFilme.duracaoFilme = duracao;
        ClearScreen();
    }while(validDigit != 1);
}

/* Movie Confirmation */
void MovieConfirmation(struct filme novoFilme) {
    time_t r;
    struct tm dataStrct = {0};
    char dataFinal[11], dataInicial[11], confirm = 0;
    
    strptime(dataInicial, "%d/%m/%Y", &dataStrct);
    r = mktime(&dataStrct);
    
    do{
        strftime(dataFinal, sizeof(dataFinal), "%d/%m/%Y", localtime(&novoFilme.dataLancamento));
       
        ClearScreen();
        
        printf(BOLDRED "Confirmação de cadastro:\n" RESET);
        printf(BOLDBLACK "\nNome do filme: \n" RESET);
        printf("%s\n\n", novoFilme.nomeFilme);
        printf(BOLDBLACK "Data de Lançamento: \n" RESET);
        printf("%s\n\n", dataFinal);
        printf(BOLDBLACK "Duração do filme: \n" RESET);
        printf("%d min\n", novoFilme.duracaoFilme);
        printf(BOLDRED "\nSalvar(1) ou descartar(2)?\n" RESET);
        printf("-> ");
        scanf("%c", &confirm);
        fseek(stdin, 0, SEEK_END);
        
        switch (confirm) {
            case '1':
                ClearScreen();
                printf(BOLDRED "Filme salvo!\n" RESET);
                AddFilme(novoFilme);
                break;
                
            case '2':
                ClearScreen();
                printf(BOLDRED "\nFilme não salvo.\n" RESET);
                break;
                
            default:
                break;
        }
    }while(confirm != '1' && confirm != '2');
}   

/* Movie List */
void MovieList() {
    
    /* Variables  */
    struct Array *filmes = GetFilmes();
    
    time_t r;
    struct tm dataStrct = {0};
    char dataFinal[11], dataInicial[11];
    
    r = mktime(&dataStrct);
    strftime(dataInicial, sizeof(dataInicial), "%d/%m/%Y", &dataStrct);
    
    if(filmes == NULL || filmes->count == 0) {
        printf(BOLDRED "\nLISTA VAZIA.\n" RESET);
    } else {
        for (int i = 0; i < filmes->count; i++) {
            strftime(dataFinal, sizeof(dataFinal), "%d/%m/%Y", localtime(&filmes->p[i].dataLancamento));
            
            printf(BOLDRED "\nID: %d)\n" RESET, i + 1);
            printf(BOLDBLACK "Nome do filme: " RESET);
            printf("%s\n", filmes->p[i].nomeFilme);
            printf(BOLDBLACK "Data de lançamento: " RESET);
            printf("%s\n", dataFinal);
            printf(BOLDBLACK "Duração do filme: " RESET);
            printf("%d min\n", filmes->p[i].duracaoFilme);
        }
    }
}
>>>>>>> 273ee77a5cfdc30de593f8191f8d4900e92564c4
