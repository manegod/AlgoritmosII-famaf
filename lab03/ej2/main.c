/*
  @file main.c
  @brief Defines main program function
*/

/* First, the standard lib includes, alphabetically ordered */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

/* Then, this project's includes, alphabetically ordered */
#include "array_helpers.h"
#include "weather.h"
#include "weather_utils.h"


/**
 * @brief print usage help
 * @param[in] program_name Executable name
 */
void print_help(char *program_name) {
    /* Print the usage help of this program. */
    printf("Usage: %s <input file path>\n\n"
           "Load climate data from a given file in disk.\n"
           "\n"
           "The input file must exist in disk and every line in it must have the following format:\n\n"
           "<year> <month> <day> <temperature> <high> <low> <pressure> <moisture> <precipitations>\n\n"
           "Those elements must be integers and will be copied into the multidimensional integer array 'a'.\n"
           "The dimensions of the array are given by the macro tclimate.\n"
           "\n\n",
           program_name);
}

/**
 * @brief reads file path from command line
 *
 * @param[in] argc amount of command line arguments
 * @param[in] argv command line arguments
 *
 * @return An string containing read filepath
 */
char *parse_filepath(int argc, char *argv[]) {
    /* Parse the filepath given by command line argument. */
    char *result = NULL;

    if (argc < 2) {
        print_help(argv[0]);
        exit(EXIT_FAILURE);
    }

    result = argv[1];

    return (result);
}

/**
 * @brief Main program function
 *
 * @param[in] argc amount of command line arguments
 * @param[in] argv command line arguments
 *
 * @return EXIT_SUCCESS when programs executes correctly, EXIT_FAILURE otherwise
 */
int main(int argc, char *argv[]) {
    char *filepath = NULL;

    /* parse the filepath given in command line arguments */
    filepath = parse_filepath(argc, argv);

    /* create an array with the type of tclimate */
    WeatherTable array;

    /* parse the file to fill the array and obtain the actual length */
    array_from_file(array, filepath);

    /* show the ordered array in the screen */
    array_dump(array);

    int hist_min = minimum_temp(array);
    printf("Lowest recorded temperature: %d\n", hist_min);

    int op[YEARS];
    maxtempt_yearly(array,op);
    for(unsigned int i = 0; i<YEARS;i++){
         printf("Max temperature on the year %d: %d\n",i+1980, op[i]);
    }

    month_t mostrain[YEARS];
    maxprec_yearly(array, mostrain);

     char *month;
    for (unsigned int year = 0; year < YEARS; year++) {
        if(mostrain[year] == 0) month = "january";
        else if(mostrain[year] == 1) month = "february";
        else if(mostrain[year] == 2) month = "march";
        else if(mostrain[year] == 3) month = "april";
        else if(mostrain[year] == 4) month = "may";
        else if(mostrain[year] == 5) month = "june";
        else if(mostrain[year] == 6) month = "july";
        else if(mostrain[year] == 7) month = "august";
        else if(mostrain[year] == 8) month = "september";
        else if(mostrain[year] == 9) month = "october";
        else if(mostrain[year] == 10) month = "november";
        else month = "december";
        printf("month with most amount of rainfall of %d: %s\n", year+1980, month);
    }

    return (EXIT_SUCCESS);
}
