#include "TrimFunc.h"
#include "string.h"
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

// Trims at begnning, middle and end;
char *StringTrimmer(char *userInput) {
    int length, i = 0, j = 0, temp = 0;
    char *start = 0;
    
    length = (int)strlen(userInput);
    start = malloc(length + 1);
    
    while (*(userInput + i) != '\0') {
        if (*(userInput + i) == ' ') { // Catches ' ' at the beginning, if not...
            temp = i + 1;
     
            if (*(userInput + temp) != '\0') {

                while (*(userInput + temp) == ' ' && *(userInput + temp) != '\0') {// while userInpu + temp is ' ' AND is NOT EOF, then....
                    if (*(userInput + temp) == ' ') { // if userInput + temp is ' '
                        i++;// increments i....
                    }
                    temp++; // ...and temp.
                }
            }
        }
        
        //                        Temp
        *(start + j) = *(userInput + i + 1); // ...gives the char to the aux string.
        i++;
        j++;
    }
    *(start + j) = '\0';
    
    return start;
}
