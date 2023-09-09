#ifndef DATE_H_
#define DATE_H_

#include <stdbool.h>
#include <stdint.h>

/***************************************
* TMSim - Date management header file
***************************************/

#define CURR_YEAR = 2023;

// stats array mappings
static char* months[12] = {
    "January",
    "February",
    "March",
    "April",
    "May",
    "June",
    "July",
    "August",
    "September",
    "October",
    "November",
    "December"
};

static uint8_t days_in_month[12] = {
    31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};

struct date {
    int16_t year;       // current year
    int16_t day;        // current day (0-364/5)
    int16_t minute;     // current minute (0-59)
};

/***** date functions *****/

// initialize the player struct based on given difficulty
void initialize_date(uint8_t, struct date*);

// determine the number of days in the current month
uint8_t get_current_month(struct date*);

// determine if the current year is a leap year
bool is_leap_year(int16_t);

#endif
