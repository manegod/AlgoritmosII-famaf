
#include <stdio.h>
#include "weather_utils.h"

int minimum_temp (WeatherTable w){
    int min = w[0][0][0]._min_temp;

    for (unsigned int year = 0; year < YEARS; year++) {
        for (unsigned int month = 0; month < MONTHS; month++) {
            for (unsigned int day = 0; day < DAYS; day++) {
                if(w[year][month][day]._min_temp < min) min = w[year][month][day]._min_temp;
            }
        }
    }

    return min;
}

void maxtempt_yearly (WeatherTable a, int output[YEARS]){
for (unsigned int year = 0; year < YEARS; year++) {
        int max_year = a[year][0][0]._max_temp;  // Inicializo
        for (unsigned int month = 0; month < MONTHS; month++) {
            for (unsigned int day = 0; day < DAYS; day++) {
                if (max_year < a[year][month][day]._max_temp) {
                    max_year = a[year][month][day]._max_temp;
                }
            }
        }
        output[year] = max_year; 
    }
}

void maxprec_yearly (WeatherTable a, month_t mostrain[YEARS]){
    for (unsigned int year = 0; year < YEARS; year++) {
        int tmp_res = 0;
        for (month_t month = 0; month < MONTHS; month++) {
            int rainfall_count = 0;
            // count the amount of rainfall in this month
            for (unsigned int day = 0; day < DAYS; day++) {
                rainfall_count += a[year][month][day]._rainfall;
            }
            if(tmp_res < rainfall_count) {
                mostrain[year] = month;
                tmp_res = rainfall_count;
            }
        }
    }
}