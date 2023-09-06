#ifndef SIM_H_
#define SIM_H_

#include <stdint.h>

#include "player.h"
#include "tm.h"

/***************************************
* TMSim - Main simulator header file
***************************************/

enum print_speeds { FAST, NORM, SLOW };

enum views {
    VIEW_INSIDE,
    VIEW_CONTROL,
    VIEW_AUXILLARY,
    VIEW_BREAKER,
    VIEW_COMPUTER,
    VIEW_CONSOLE,
    VIEW_STORAGE,
    VIEW_REPAIRS,
    VIEW_OUTSIDE
};

// view menu actions - ASCII 0-9
enum view_actions {
    ACTION_ZERO = 0x30,
    ACTION_ONE,
    ACTION_TWO,
    ACTION_THREE,
    ACTION_FOUR,
    ACTION_FIVE,
    ACTION_SIX,
    ACTION_SEVEN,
    ACTION_EIGHT,
    ACTION_NINE
};

// general actions - ASCII letters
#define ACTION_HELP     0x48    // uppercase H
#define ACTION_LOOK     0x4C    // uppercase L
#define ACTION_PAUSE    0x50    // uppercase P

/***** string constants *****/

static char panel_line[]  = "    ---------------------------------------------\n";
static char panel_line2[] = "    |----------|----------|----------|----------|\n";
static char breaker_line[]  = "-------------------------------------------------------------\n";

static char* breaker_disp[] = {"NOM", "FLT" };

static char* general_actions[] = {
    "  - H - get this HELP page\n",
    "  - L - get a LOOK around again\n",
    "  - P - PAUSE the simulator\n"
};
#define GEN_ACTIONS     (sizeof(general_actions)/sizeof(general_actions[0]))

/***** main simulator functions *****/

// the main simulator control loop
void sim_loop(struct time_machine*, struct player*);

// sim loop wrapper function for entering and exiting simulator
void enter_sim_loop(struct time_machine*, struct player*);

/***** simulator view functions *****/

// view - sitting inside the time machine
void view_inside(struct time_machine*, struct player*);

// view - looking at the main control panel
void view_control_panel(struct time_machine*, struct player*);

// view - looking at the auxillary control panel
void view_aux_panel(struct time_machine*, struct player*);

// view - looking at the breaker panel
void view_breaker_panel(struct time_machine*, struct player*);

// view - looking at the computer when it or the console is off
void view_computer(struct time_machine*, struct player*);

// view - looking at the time machine console
void view_console(struct time_machine*, struct player*);

// view - looking at the storage compartment
void view_storage(struct time_machine*, struct player*);

// view - outside of the time machine
void view_outside(struct time_machine*, struct player*);

// view - repairing the time machine
void view_repairs(struct time_machine*, struct player*);

/***** simulator action functions *****/

// action - get some help
void action_help(void);

// action - pause the game
void action_pause(struct player*);

// action - press one of the critical or auxillary buttons
void action_button(struct time_machine*, struct player*, uint8_t, bool);

// action - trip or reset one of the circuit breakers
void action_breaker(struct time_machine*, struct player*, uint8_t, bool);

// action - attempt to engage the critical power lockout
void action_power_lock(struct time_machine*, struct player*);

/***** simulator helper routines *****/

// narrate the game with the tmprint function
void narrate(char*, uint8_t);

// interpret provided response for letter-based actions from the player
void check_general_actions(struct time_machine*, struct player*, int);

// check which computer view to use.
void check_computer(struct time_machine*, struct player*);

#endif