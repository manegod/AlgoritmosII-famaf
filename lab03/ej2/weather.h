/*
  @file weather.h
  @brief Defines weather mesuarement structure and methods
*/

#ifndef _WEATHER_H
#define _WEATHER_H
#define EXPECTED_WEATHER_FILE_FORMAT "%d %d %d %u %u %u"
#include <stdio.h>

/** @brief Type used to represent a weather mesuarement.*/
typedef struct _weather
{
    int _average_temp;      //average temperature
    int _max_temp;          //max temperature
    int _min_temp;          //min temp
    unsigned int _pressure; //pressure
    unsigned int _moisture; //moisture
    unsigned int _rainfall; //rainfall
} Weather;

/**
 * @brief reads weather mesureament from file line
 * @details
 * Weather file line must contain:
 * <int> <int> <int> <unsigned int> <unsigned int> <unsigned int>
 *
 * @param[in] file Opened file stream
 * @return Weather structure which contain read information from file
 */
Weather weather_from_file(FILE* file);

/**
 * @brief writes weather information into opened file stream
 * @details
 * The line will be written using this format:
 * <avg_temp> <max_temp> <min_temp> <pressure> <moisture> <rainfall>
 *
 * @param[in] file Opened file stream
 * @param[in] weather Weather mesuarement to be written
 */
void weather_to_file(FILE* file, Weather weather);


#endif //_WEATHER_H
