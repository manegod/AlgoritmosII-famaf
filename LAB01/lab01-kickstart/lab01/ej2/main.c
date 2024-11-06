/* First, the standard lib includes, alphabetically ordered */
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/* Maximum allowed length of the array */
#define MAX_SIZE 100000

void print_help(char *program_name) {
    /* Print the usage help of this program. */
    printf("Usage: %s <input file path>\n\n"
           "Loads an array given in a file in disk and prints it on the screen."
           "\n\n"
           "The input file must have the following format:\n"
           " * The first line must contain only a positive integer,"
           " which is the length of the array.\n"
           " * The second line must contain the members of the array"
           " separated by one or more spaces. Each member must be an integer."
           "\n\n"
           "In other words, the file format is:\n"
           "<amount of array elements>\n"
           "<array elem 1> <array elem 2> ... <array elem N>\n\n",
           program_name);
}

char *parse_filepath(int argc, char *argv[]) {
    /* Parse the filepath given by command line argument. */
    char *result = NULL;
    // Program takes exactly two arguments
    // (the program's name itself and the input-filepath)
    bool valid_args_count = (argc == 2);

    if (!valid_args_count) {
        print_help(argv[0]);
        exit(EXIT_FAILURE);
    }

    result = argv[1];

    return result;
}

unsigned int array_from_stdin(int array[],
                             unsigned int max_size){

    unsigned int length;
    max_size = MAX_SIZE;

    printf("Enter a valid value for the array length\n");

    if (fscanf (stdin,"%u", &length)!=1 || length<=0 || length>max_size){
        printf ("ERROR. INVALID VALUE.");
        exit(EXIT_FAILURE);
    }
    printf ("Enter the array values\n");

    for (unsigned int i = 0; i<length; i++){
       if (fscanf (stdin,"%d", &array[i])!=1){
        printf ("ERROR. INVALID VALUE.");
        exit(EXIT_FAILURE);
       }
    }

return length;
}

void array_dump(int a[], unsigned int length) {
    
    printf("[ ");
    for (unsigned int i = 0; i<length-1; i++){
        
        printf ("%d, ", a[i]);
    } 
    printf ("%d]\n", a[length-1]);
    


}


int main(int argc, char *argv[]) {

    /* create an array of MAX_SIZE elements */
    int array[MAX_SIZE];
    
    /* parse the file to fill the array and obtain the actual length */
    unsigned int length = array_from_stdin(array, MAX_SIZE);
    
    /*dumping the array*/
    array_dump(array, length);
    
    return EXIT_SUCCESS;
}
