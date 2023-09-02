#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "tm.h"

/***************************************
* TMSim - Time machine module
***************************************/

/***** init functions *****/

/* Rolls a part status with a 25% variance
*    Difficulty is on a 1-5 sliding scale:
*    Difficulty 1 = 0-25% per part
*    Difficulty 5 = 40-65% per part
*/
uint8_t roll_part(uint8_t difficulty) {
    uint8_t rando = rand() % 25;
    return rando + (difficulty - 1) * 10;
}

void roll_parts(uint8_t difficulty, struct time_machine_parts* parts) {
    for (int i = 0; i < 6; i++) {
        parts->critical[i].wear = roll_part(difficulty);
        parts->critical[i].tear = roll_part(difficulty);
        parts->auxillary[i].wear = roll_part(difficulty);
        parts->auxillary[i].tear = roll_part(difficulty);
        parts->computer[i].wear = roll_part(difficulty);
        parts->computer[i].tear = roll_part(difficulty);
    }
}

void initialize_tm(uint8_t difficulty, struct time_machine* tm) {
    tm->energy = rand() % 250 + difficulty * 1000 - 250;
    roll_parts(difficulty, &(tm->parts));

    tm->crit_power = PWR_LOCK_ON - 1;       // crit parts on
    tm->crit_status = CRITICAL_OK - 1;      // crit parts ok

    tm->aux_power = 0;                      // aux parts off
    tm->aux_status = CRITICAL_OK - 1;       // aux parts ok
}

/***** bitwise helper functions *****/

bool get_power_status(struct time_machine* tm, uint8_t part, bool is_crit) {
    if (is_crit) {
        return tm->crit_power & (uint8_t)pow(2, part);
    } else {
        return tm->aux_power & (uint8_t)pow(2, part);
    }
}

bool get_fault_status(struct time_machine* tm, uint8_t part, bool is_crit) {
    if (is_crit) {
        return !(tm->crit_status & (uint8_t)pow(2, part));
    } else {
        return !(tm->aux_status & (uint8_t)pow(2, part));
    }
}

void set_bits(uint8_t* byte, uint8_t mask) {
    *byte = *byte | mask;
}

void unset_bits(uint8_t* byte, uint8_t mask) {
    *byte = *byte & ~mask;
}

/***** data refresh functions *****/

void refresh_power_data(struct time_machine* tm) {
    // bitwise check if lower 6 exterior power bits are set (7th bit - 1)
    if (tm->crit_power & (CRITICAL_ON - 1) == CRITICAL_ON - 1) {
        set_bits(&tm->crit_power, CRITICAL_ON);
    } else {
        unset_bits(&tm->crit_power, CRITICAL_ON);
    }
    // bitwise check if lower 6 exterior power bits are set (7th bit - 1)
    if (tm->crit_status & (CRITICAL_OK - 1) == CRITICAL_OK - 1) {
        set_bits(&tm->crit_status, CRITICAL_OK);
    } else {
        unset_bits(&tm->crit_status, CRITICAL_OK);
    }
}

void refresh_part_status(struct time_machine* tm) {
    uint8_t worst = NOM;
    uint8_t pc_worst = NOM;
    uint8_t cond;
    for (uint8_t i = 0; i < 6; i++) {
        cond = get_part_status(get_condition(get_part(i, CRITICAL, tm)));
        tm->status.critical[i] = cond;
        worst = cond > worst ? cond : worst;
        cond = get_part_status(get_condition(get_part(i, AUXILLARY, tm)));
        tm->status.auxillary[i] = cond;
        worst = cond > worst ? cond : worst;
        cond = get_part_status(get_condition(get_part(i, COMPUTER, tm)));
        pc_worst = cond > pc_worst ? cond : pc_worst;
        worst = cond > worst ? cond : worst;        
    }
    tm->status.computer = pc_worst;
    tm->tm_status = worst;
}

/***** data retrieval functions *****/

struct time_machine_part* get_part(uint8_t id, uint8_t type, struct time_machine* tm) {
    struct time_machine_part* part;

    switch (type) {
    case CRITICAL:  part = &tm->parts.critical[id];     break;
    case AUXILLARY: part = &tm->parts.auxillary[id];    break;
    case COMPUTER:  part = &tm->parts.computer[id];     break;
    default:    printf("Something went wrong in get_part()\n");
    }

    return part;
}

uint8_t get_condition(struct time_machine_part* part) {
    return (part->wear + part->tear * 2) / 3;
}

uint8_t get_part_status(uint8_t cond) {
    if (cond < 33) {
        return NOM;
    } else if (cond < 66) {
        return INF;
    } else if (cond < 100) {
        return WRN;
    } else {
        return FLT;
    }
}

/***** data manipulation routines *****/

void wear_part(struct time_machine_part* part) {
    part->wear += rand() % 5;
    tear_part(part);
}

void tear_part(struct time_machine_part* part) {
    part->tear += rand() % (5 * (part->wear / 20));
}

void power_part(uint8_t id, bool is_crit, bool status, struct time_machine* tm) {
    void (*bitop)(uint8_t*, uint8_t) = status ? &set_bits : &unset_bits;
    if (is_crit) {
        (*bitop)(&tm->crit_power, (uint8_t)pow(2, id));
    } else {
        (*bitop)(&tm->aux_power, (uint8_t)pow(2, id));
    }
}

void reset_part(uint8_t id, bool is_crit, bool status, struct time_machine* tm) {
    void (*bitop)(uint8_t*, uint8_t) = status ? &set_bits : &unset_bits;
    if (is_crit) {
        (*bitop)(&tm->crit_status, (uint8_t)pow(2, id));
    } else {
        (*bitop)(&tm->aux_status, (uint8_t)pow(2, id));
    }
}

bool turn_on_part(uint8_t id, bool is_crit, struct time_machine* tm) {
    struct time_machine_part* part = get_part(id, is_crit, tm);
    uint8_t flt_byte = is_crit ? tm->crit_status : tm->aux_status;
    uint8_t cond = get_condition(part);
    uint8_t chance = 9/10 * cond + 5;
    if (rand() % 100 < chance) {
        power_part(id, is_crit, ON, tm);
        return true;
    } else {
        reset_part(id, is_crit, OFF, tm);
        return false;
    }
}

void turn_off_part(uint8_t id, bool is_crit, struct time_machine* tm) {
    // TODO: this should check for 
    power_part(id, is_crit, OFF, tm);
}

/***** print functions *****/

char* print_critical_part(uint8_t part) {
    switch (part) {
    case POWER:     return "Power Distrib. Unit";   break;
    case SUPPORT:   return "Life Support System";   break;
    case AIRLOCK:   return "Time Machine Airlock";  break;
    case CIRCUITS:  return "Time Travel Circuits";  break;
    case CONSOLE:   return "Console and Keyboard";  break;
    case RC2014:    return "RC2014 Microcomputer";  break;
    case ALL_CRIT:  return "All Critical Systems";  break;
    case PWR_LOCK:  return "Power Lockout Switch";  break;
    default:        return "Something went wrong";
    }
}

char* print_auxillary_part(uint8_t part) {
    switch (part) {
    case SENSORS:   return "Threat Sensor System";  break;
    case SHIELD:    return "Insibility Shield";     break;
    case HOVER:     return "Hover Propulsion";      break;
    case TESLA:     return "Tesla Charging Coil";   break;
    case FUSION:    return "Mr Fusion Reactor";     break;
    case STEAM:     return "Steam Charging Unit";   break;
    default:    return "Something went wrong";
    }
}

char* print_computer_part(uint8_t part) {
    switch (part) {
    case BACKPLANE: return "System Backplane";      break;
    case CLOCK:     return "Dual System Clock";     break;
    case Z80_CPU:   return "Z80 Processor Board";   break;
    case MEMORY:    return "RAM/ROM Memory Unit";   break;
    case SERIAL_IO: return "Dual Serial I/O";       break;
    case HW_BRIDGE: return "TM Hardware Bridge";    break;
    default:    return "Something went wrong";
    }
}

char* print_power_status(struct time_machine* tm, uint8_t part, bool is_crit) {
    if (get_fault_status(tm, part, is_crit)) {
        return power_str[IS_FLT];
    } else {
        return power_str[get_power_status(tm, part, is_crit)];
    }
}

char* status_disp(uint8_t id) {
    switch (id) {
    case 0:     return "NOM";   break;
    case 1:     return "INF";   break;
    case 2:     return "WRN";   break;
    case 3:     return "FLT";   break;
    default:    printf("Something went wrong in statusdisp()");
    }
    return "ERR";
}
