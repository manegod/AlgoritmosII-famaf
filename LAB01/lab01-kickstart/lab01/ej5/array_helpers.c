#include <assert.h>
#include "mybool.h"  
#include <stdio.h>
#include <stdlib.h>

#include "array_helpers.h"

#define MAX_SIZE 100000

unsigned int array_from_file(int array[],
                             unsigned int max_size,
                             const char *filepath) {

    unsigned int length;
    max_size = MAX_SIZE;
    FILE *f = fopen (filepath, "r"); //abro el archivo y le asigno un puntero
    if (f==NULL){
        printf("ERROR. File does not exist.");
 
        exit(EXIT_FAILURE);
    } 
    if (fscanf(f, "%u",&length)==0|| length > max_size) {
        printf("ERROR. UNVALID LENGTH.");

        exit(EXIT_FAILURE);
    }



    for (unsigned int i = 0; i < length; i++){
        if ((fscanf(f,"%d",&array[i]))!=1){
            printf("ERROR. Mismatching number of elements.");
 
            exit(EXIT_FAILURE);
        }
    }
    
fclose (f);
return length;
}


void array_dump(int a[], unsigned int length) {
    
    printf("[ ");
    for (unsigned int i = 0; i<length-1; i++){
        
        printf ("%d, ", a[i]);
    } 
    printf ("%d]\n", a[length-1]);

}

mybool array_is_sorted(int a[], unsigned int length){

mybool value = true;

for (unsigned int i = 0; i<length-1; i++){
    if (a[i]>a[i+1]){
        value = false;

    }
}

return value;
}