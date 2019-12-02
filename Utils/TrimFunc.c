#include "TrimFunc.h"
#include "string.h"
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

char *StringTrimmer(char *userInput) {
    int length = 0, i = 0, j = 0, temp = 0;
    char *start = 0;
    
    length = (int)strlen(userInput);
    start = malloc(length + 1);
    
    while (*(userInput + i) != '\0') {
        
        if (*(userInput + i) == ' ') {
            temp = i + 1;
            
            if (*(userInput + temp) != '\0') {
                while (*(userInput + temp) == ' ' && *(userInput + temp) != '\0') {
                    if (*(userInput + temp) == ' ') {
                        i++;
                    }
                    temp++;
                }
            }
        }
        
        if (j == 0 && *(userInput + i) == ' ') {
            i++;
        }
        
        *(start + j) = *(userInput + i);
        i++;
        j++;
    }
    
    *(start + j - 1)     = '\0';
    return start;
}
