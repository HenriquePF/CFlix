#include "TrimFunc.h"
#include "string.h"
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

/* TODO -> 1) Make 'em into only one function */

char *StringTrimmer(char *nomeFilme) {
    int length, i = 0, j = 0;
    char *start;
    
    length = (int)strlen(nomeFilme);
    
    start = (char*) malloc(length + 1);
    
    while (*(nomeFilme + i) != '\0') {
        if (*(nomeFilme + i) == ' ') {
            int temp = i + 1;
            if (*(nomeFilme + temp) != '\0') {
                while (*(nomeFilme + temp) == ' ' && *(nomeFilme + temp) != '\0') {
                    if (*(nomeFilme + temp) == ' ') {
                        i++;
                    }
                    temp++;
                }
            }
        }
        *(start + j) = *(nomeFilme + i);
        i++;
        j++;
    }
    *(start + j)= '\0';
    
    return start;
}

void TrimTrailing(char *nomeFilme) {
    int index, i;
    index = 0;
    
    i = 0;
    while(nomeFilme[i] != '\0') {
        if(nomeFilme[i] != ' ' && nomeFilme[i] != '\t' && nomeFilme[i] != '\n') {
            index= i;
        }
        
        i++;
    }
    
    nomeFilme[index + 1] = '\0';
}

// Not used
void trimLeading(char *nomeFilme) {
    int index, i;
    
    index = 0;
    
    while(nomeFilme[index] == ' ' || nomeFilme[index] == '\t' || nomeFilme[index] == '\n') {
        index++;
    }
    
    
    if(index != 0) {
        i = 0;
        while(nomeFilme[i + index] != '\0') {
            nomeFilme[i] = nomeFilme[i + index];
            i++;
        }
        nomeFilme[i] = '\0';
    }
}
