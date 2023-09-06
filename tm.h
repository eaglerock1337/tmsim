#ifndef TM_H_
#define TM_H_

#include <stdbool.h>
#include <stdint.h>

/***************************************
* TMSim - Time machine header file
***************************************/

// power constants
enum powers { OFF, ON, IS_FLT };

static char* power_str[] = {"OFF", "ON", "FLT"};

/****** enum constants *****/

// basic constants
enum statuses { NOM, INF, WRN, FLT };
enum part_types { AUXILLARY, CRITICAL, COMPUTER };

// part IDs
enum critical_part_ids {
    POWER,
    SUPPORT,
    AIRLOCK,
    CIRCUITS,
    CONSOLE,
    RC2014,
    ALL_CRIT,
    PWR_LOCK
};

enum auxillary_part_ids {
    SENSORS,
    SHIELD,
    HOVER,
    TESLA,
    FUSION,
    STEAM
};

enum computer_part_ids {
    BACKPLANE,
    CLOCK,
    Z80_CPU,
    MEMORY,
    SERIAL_IO,
    HW_BRIDGE
};

// bitwise values
enum critical_bitwise_values {
    POWER_ON = 1,
    SUPPORT_ON = 2,
    AIRLOCK_ON = 4,
    CIRCUITS_ON = 8,
    CONSOLE_ON = 16,
    RC2014_ON = 32,
    CRITICAL_ON = 64,
    PWR_LOCK_ON = 128
};

enum critical_bitwise_status {
    POWER_OK = 1,
    SUPPORT_OK = 2,
    AIRLOCK_OK = 4,
    CIRCUITS_OK = 8,
    CONSOLE_OK = 16,
    RC2014_OK = 32,
    CRITICAL_OK = 64,
    PWR_LOCK_OK = 128
};

enum auxillary_bitwise_values {
    SENSORS_ON = 1,
    SHIELD_ON = 2,
    HOVER_ON = 4,
    TESLA_ON = 8,
    FUSION_ON = 16,
    STEAM_ON = 32
};

enum auxillary_bitwise_status {
    SENSORS_OK = 1,
    SHIELD_OK = 2,
    HOVER_OK = 4,
    TESLA_OK = 8,
    FUSION_OK = 16,
    STEAM_OK = 32
};

/***** data structures *****/

// a single time machine part's wear & tear values
struct time_machine_part {
    uint8_t wear;       // part's wear value from 0-100%
    uint8_t tear;       // part's tear value from 0-100%
};

// the time machine's complete part wear & tear value set
struct time_machine_parts {
    struct time_machine_part critical[6];   // core part value array
    struct time_machine_part auxillary[6];  // aux part value array
    struct time_machine_part computer[6];   // rc2014 part value array
};

// the time machine's display status for all parts
struct time_machine_status {
    // TODO: optimize this later with 2 2-bit words
    uint8_t critical[6];    // 6 exterior part values
    uint8_t auxillary[6];
    uint8_t computer;       // single switch
};

// the time machine's memory bank (lost on reset)
struct time_machine_ram {
    uint8_t aggro;                      // detected aggro
    struct time_machine_parts parts;    // detected part data
};

struct time_machine {
    uint32_t energy;                    // total energy in kJ
    struct time_machine_parts parts;    // wear & tear
    struct time_machine_status status;  // display statuses
    uint8_t tm_status;                  // overall system status

    uint8_t crit_power;                 // bitwise power
    uint8_t crit_status;                // bitwise status

    uint8_t aux_power;                  // bitwise power
    uint8_t aux_status;                 // bitwise status
};

/***** init functions *****/

// rolls a single part status based on a 1-5 difficulty
uint8_t roll_part(uint8_t);

// roll time machine part stats based on a 1-5 difficulty
void roll_parts(uint8_t, struct time_machine_parts*);

// new game time machine initialization routine
void initialize_tm(uint8_t, struct time_machine*);

/***** bitwise helper functions *****/

// get power status based on part ID and type
bool get_power_status(struct time_machine*, uint8_t, bool);

// get fault status based on part ID and type
bool get_fault_status(struct time_machine*, uint8_t, bool);

// set a bit or bits with the provided mask
void set_bits(uint8_t* byte, uint8_t mask);

// unset a bit or bits with the provided mask
void unset_bits(uint8_t* byte, uint8_t mask);

/***** data refresh functions *****/

// refresh the power status of the time machine
void refresh_power_data(struct time_machine*);

// refresh the display status for all time machine parts
void refresh_part_status(struct time_machine*);

/***** data retrieval functions *****/

// get the time machine part based on its id and type
struct time_machine_part* get_part(uint8_t, uint8_t, struct time_machine*);

// return the overall wear/tear condition of the part
uint8_t get_condition(struct time_machine_part*);

// get the part status of a given overall part wear status from 0-100
uint8_t get_part_status(uint8_t);

/***** data manipulation routines *****/

// perform wear and tear on a given part
void wear_part(struct time_machine_part*);

// perform part tear on a given part
void tear_part(struct time_machine_part*);

// turn on a part on or off based on part id and if critical
void power_part(uint8_t, bool, bool, struct time_machine*);

// fault or reset a part based on part id and if critical
void reset_part(uint8_t, bool, bool, struct time_machine*);

// attempt to turn on a part & return 1 if successful
bool turn_on_part(uint8_t, bool, struct time_machine*);

// turn off the specified part by id and if it is critical
void turn_off_part(uint8_t, bool, struct time_machine*);

/***** print functions *****/

// returns a critical part name based on its array ID
char* print_critical_part(uint8_t);

// returns an auxillary part name based on its array ID
char* print_auxillary_part(uint8_t);

// returns a computer part name based on its array ID
char* print_computer_part(uint8_t);

// returns a printable power status based on ID
char* print_power_status(struct time_machine*, uint8_t, bool);

// return the status display for the given status id
char* status_disp(uint8_t);

#endif

/* Time Machine TODOs
*   TODO: minimum energy amount for stuff:
*       25kj minimum for base for 1 hour
*       25kj minimum for TDOS for 1 hour
*       1gj for time travel
*   Time travel formula:
*   Energy = Years ^ 2 / 4300 + 1
*       30 years = 1.21gj - because it has to, obviously
*   TODO: time travel routine has a max gj rating check
*/