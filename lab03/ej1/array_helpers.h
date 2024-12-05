#ifndef _ARRAY_HELPERS_H
#define _ARRAY_HELPERS_H

#include <stdbool.h>

unsigned int
data_from_file(const char *path,
                unsigned int indexes[],
                char letters[],
                unsigned int max_size);
/*
Reads the data from file and returns how many elements the file had.
 */


void dump(char a[], unsigned int length);
/*
    Write the content of the array 'a' into stdout. The array 'a' must have
    exactly 'length' elements.

*/

void sorting_order (unsigned int indexes[], 
                char letters[], 
                char sorted[], 
                unsigned int lenght);

/*Sorts the letters to make the word*/
#endif
