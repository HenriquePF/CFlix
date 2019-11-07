#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Filme.h"

void RemoveMovie(struct Array *a, int index) {
    int i, j = 0;
    
    struct filme *temp = malloc(sizeof(a->p));
    
    for (i = 0; i < a->count; i++) {
        if (i != index) {
            temp[j] = a->p[i];
            j++;
        }
    }
    
    a->count = a->count - 1;
    a->reserved = a->count;
    free(a->p);
    a->p = temp;
}

void AddElement(struct Array *a, struct filme inputValue) {
    struct filme *temp;
    if(a->p == NULL) {
        a->p = (struct filme *)malloc(sizeof(struct filme) * 1);
        a->reserved++;
    }
    
    if(a->count == a->reserved) {
        int i = 0;
        temp = malloc(sizeof(struct filme) * (a->count * 2));
        a->reserved = a->count * 2;
        
        for(i = 0; i < a->count; i++) {
            temp[i] = a->p[i];
        }
        
        free(a->p);
        a->p = temp;
    }
    
    a->p[a->count] = inputValue;
    a->count++;
}

/* Globals */
/* Struct array global to be used by addElement */
struct Array g_filmes = {0};

void DeleteFilme(struct Array *f, int index) {
    RemoveMovie(f, index);
}

void AddFilme(struct filme f) {
    AddElement(&g_filmes, f);
}

struct Array *GetFilmes(void) {
    // TODO: Fazer uma cópia
    
    return &g_filmes;
}
