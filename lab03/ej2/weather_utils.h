#ifndef _WEATHER_UTILS
#include <stdio.h>
#include "weather.h"
#include "array_helpers.h"

//#define DATOS weather_array

//Weather DATOS[YEARS];

int minimum_temp (WeatherTable w); //Obtains hystorical minimum temperature.

void maxtempt_yearly (WeatherTable a, int output[YEARS]);

void maxprec_yearly (WeatherTable a, month_t mostrain[YEARS]);
#endif