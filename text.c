#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "text.h"

/***************************************
* TMSim - Text management module
***************************************/

void tmprint(char* str, uint8_t type) {
    for (uint8_t i = 0; i < strlen(str); i++) {
        putc(str[i], stdout);
        fflush(stdout);         // flush stdout buffer
        delay(delays[type]);
    }
}

void delay(uint16_t length) {
    // TODO: work in rtc computer compatibility stuffs here
    for (uint16_t i = 0; i < length; i++) {
        for (uint16_t j = 0; j < DELAYLOOP; j++);
    }
}

void lineprint(char dash, uint8_t size) {
    for (uint8_t i = 0; i < size; i++) putc(dash, stdout);
    putc('\n', stdout);
    delay(4096);
    putc('\n', stdout);
}

int get_response(void) {
    tmprint("\nWhat would you like to do? (press a # or h for help): ", NORM_NARR);
    scanf("%s", input);
#ifdef RC   // this is way easier than dealing with C compiler pragmas
        printf("\n");
#endif
    return toupper((int)input[0]);
}

bool confirm(void) {
    tmprint("Are you sure? Type 'yes' to confirm: ", NORM_NARR);
    scanf("%s", input);
    for (int i = 0; i < strlen(input); i++) {
        input[i] = toupper(input[i]);
    }
    printf("Cheoprint: %s", input);
    return strcmp(input, "YES") == 0 ? true : false;
}