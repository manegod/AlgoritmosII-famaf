#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>


unsigned int data_from_file(const char *path,
                unsigned int indexes[],
                char letters[],
                unsigned int max_size){

    unsigned int lenght = 0; //will count how many elements have been read

    FILE *file = fopen(path, "r"); //path will be the file to be opened, r (reading) is the mode 

    if (file == NULL){
        printf("ERROR: There's no file to open\n");
        exit(EXIT_FAILURE);
    }

    for (unsigned int i = 0; i<max_size && !(feof(file)); i++){
        if(fscanf(file,"%u -> *%c*", &indexes[i], &letters[i])==2){
            lenght ++;
        }
    }

    for (unsigned int i = 0; i < lenght; i++){
        
            if (indexes[i]>= lenght){
                printf("ERROR! The index value is larger than the word!!\n");
                exit(EXIT_FAILURE);
            
        }
    }

fclose(file);

return lenght;

}


void dump(char a[], unsigned int length) {
   // printf("\"");
    for (unsigned int j=0u; j < length; j++) {
        printf("%c", a[j]);
    }
  //  printf("\"");
    printf("\n");
}



void sorting_order (unsigned int indexes[], 
                char letters[], 
                char sorted[], 
                unsigned int lenght){

    for (unsigned int i = 0; i<lenght; i++){ //this 'i' is for checking the correct order
      //  printf("indexes[%u] = %u, letters[%u] = %c\n", i, indexes[i], i, letters[i]);
        for (unsigned int j = 0; j<lenght; j++){ // this 'j' is for moving thru the array to check if it matches the position
            if( i == indexes[j]){            //verifies that the element in indexes is "in order"
                sorted[i] = letters[j]; 
               // printf("sorted [%u]=%c\n",i,sorted[i]);     //if it is, saves it in sorted
            }
        }
    }
}