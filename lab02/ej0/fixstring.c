#include <stdbool.h>
#include <assert.h>
#include <stdio.h>

#include "fixstring.h"


unsigned int fstring_length(fixstring s) {

unsigned int lenght = 1; //makes sure to count the '\0'.
unsigned int i = 0;

    if (s == NULL){
        printf("ERROR: LISTA INVALIDA");
        return 0;
    }
    while (i<FIXSTRING_MAX && s[i]!= '\0'){
        lenght++;
        i++;
    }

return lenght;
}

bool fstring_eq(fixstring s1, fixstring s2) {

unsigned int lenght1 = fstring_length (s1);
unsigned int lenght2 = fstring_length (s2);

unsigned int i;
bool res = true;

    if (lenght1 == lenght2){
        for (i = 0; i < lenght1+1; i++){
            if (s1[i] != s2[i]){
                res = false;
            }
        }
    }
return res;
}


bool fstring_less_eq(fixstring s1, fixstring s2) {

unsigned int length = fstring_length(s1);

bool value = true;

    for (unsigned int i = 0; i < length && value; i++) {
        if (s1[i] < s2[i]) {
            return value; 
        }         
        else if (s1[i] == s2[i]){
             value = true;    
        } 
        else {
            value = false; 
        }
    }

    return value;
}

