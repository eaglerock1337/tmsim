#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "date.h"

/***************************************
* TMSim - Date management module
***************************************/

void initialize_date(uint8_t difficulty, struct date* d) {
    // harder difficulties start closer to Roman Empire
    d->year = 500 - 500 * difficulty + rand() % 100;
    d->day = rand() % 365;  // no 12/31 on leap years
    d->minute = rand() % 1440;
}

uint8_t get_current_month(struct date* d) {
    int16_t last_day = (int16_t)days_in_month[0];
    for (uint8_t i = 0; i < 12; i++) {
        if (i == 1 && is_leap_year(d->year)) { 
            last_day++;     // add a leap day in February
        }
        if (d->day < last_day) {
            return i;
        }
    }
    printf("Error: date is invalid\n");
    return 255;
}

bool is_leap_year(int16_t year) {
    if (year % 400 == 0) { return true; }
    if (year % 100 == 0) { return false; }
    if (year % 4 == 0)  { return true; }
    return false;
}