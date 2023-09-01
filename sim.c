#include <ctype.h>
#include <stdint.h>
#include <stdio.h>

#include "player.h"
#include "sim.h"
#include "tdos.h"
#include "text.h"
#include "tm.h"

/***************************************
* TMSim - Main simulator module
***************************************/

void sim_loop(struct time_machine* tm, struct player* p) {
    while (!p->paused) {
        switch (p->view) {
        case VIEW_INSIDE:       view_inside(tm, p);         break;
        case VIEW_CONTROL:      view_control_panel(tm, p);  break;
        case VIEW_AUXILLARY:    view_aux_panel(tm, p);      break;
        case VIEW_BREAKER:      view_breaker_panel(tm, p);  break;
        case VIEW_COMPUTER:     view_computer(tm, p);       break;
        case VIEW_CONSOLE:      view_console(tm, p);        break;
        case VIEW_STORAGE:      view_storage(tm, p);        break;
        case VIEW_OUTSIDE:      view_outside(tm, p);        break;
        case VIEW_REPAIRS:      view_repairs(tm, p);        break;
        default:    printf("Something went wrong in sim_loop()\n");
        }
    }
}

void enter_sim_loop(struct time_machine* tm, struct player* p) {
    p->paused = false;
    p->new_view = true;
    lineprint('=', 64);
    narrate("**** You are now entering the simulation. ****\n\n", NORM);
    lineprint('=', 64);
    delay(4096);
    refresh_part_status(tm);
    refresh_power_data(tm);
    sim_loop(tm, p);
    lineprint('=', 64);
    narrate("**** Simulation paused. Returning to main menu. ****\n\n", NORM);
    lineprint('=', 64);
    delay(4096);
}

/***** simulator view functions *****/

void view_inside(struct time_machine* tm, struct player* p) {
    if (p->new_view) {
        p->new_view = false;
        narrate("\nYou are sitting inside the time machine.\n", NORM);
        narrate("\nAmidst the mess of wires and exposed circuitry, you can look at\n"
                " |1| the main CONTROL panel, the |2| AUXILLARY control panel,\n", FAST);
        narrate(" |3| the circuit BREAKER panel,  |4| the COMPUTER and CONSOLE,\n"
                " |5| a STORAGE compartment, and  |6| the airlock to the OUTSIDE.\n", FAST);
        narrate("You can also |7| make REPAIRS or |8| get some REST.\n", FAST);
    } else {
        narrate("\nYou are still sitting inside the time machine.\n", NORM);
    }
    delay(2048);
    input[0] = get_response();     // pull one char into the input buffer
    switch(input[0]) {
    case ACTION_ONE:    p->view = VIEW_CONTROL;     p->new_view = true;     break;
    case ACTION_TWO:    p->view = VIEW_AUXILLARY;   p->new_view = true;     break;
    case ACTION_THREE:  p->view = VIEW_BREAKER;     p->new_view = true;     break;
    case ACTION_FOUR:   check_computer(tm, p);      p->new_view = true;     break;
    case ACTION_FIVE:   p->view = VIEW_STORAGE;     p->new_view = true;     break;
    case ACTION_SIX:    p->view = VIEW_OUTSIDE;     p->new_view = true;     break;
    case ACTION_SEVEN:  p->view = VIEW_REPAIRS;     p->new_view = true;     break;
    case ACTION_EIGHT:  narrate("No rest for the wicked.\n", SLOW);         break;
    default:            check_general_actions(tm, p, input[0]);
    }
}

void view_control_panel(struct time_machine* tm, struct player* p) {
    if (p->new_view) {
        p->new_view = false;
        narrate("\nYou are looking at the main control panel.\n", NORM);
        narrate("\nThe panel, labeled 'CRITICAL PARTS', shows the following:\n", NORM);
        narrate(panel_line, FAST);
        narrate("    |Power Bank|Power Unit|Life Supp.| Air Lock |\n", FAST);
        narrate(panel_line2, FAST);
        snprintf(print, PRINT_BUF, "    | %6ikJ | |1| %3s  | |2| %3s  | |3| %3s  |\n",
                 tm->energy, get_power_status(tm, POWER, true),
                 get_power_status(tm, SUPPORT, true),
                 get_power_status(tm, AIRLOCK, true));
        narrate(print, FAST);
        narrate(panel_line, FAST);
        narrate("    |Time Circ.| Console  | Computer |Power Lock|\n", FAST);
        narrate(panel_line2, FAST);
        snprintf(print, PRINT_BUF, "    | |4| %3s  | |5| %3s  | |6| %3s  | |7| %3s  |\n",
                 get_power_status(tm, CIRCUITS, true),
                 get_power_status(tm, CONSOLE, true),        
                 get_power_status(tm, COMPUTER, true),
                 get_power_status(tm, PWR_LOCK, true));
        narrate(print, FAST);
        narrate(panel_line, FAST);
        narrate("You can press one of the numbered buttons or |0| look away.\n", FAST);
    } else {
        narrate("\nYou are still looking at the main control panel.\n", NORM);
    }
    delay(2048);
    input[0] = get_response();     // pull one char into the input buffer
    switch(input[0]) {
    case ACTION_ONE:    action_button(tm, p, POWER, true);      break;
    case ACTION_TWO:    action_button(tm, p, SUPPORT, true);    break;
    case ACTION_THREE:  action_button(tm, p, AIRLOCK, true);    break;
    case ACTION_FOUR:   action_button(tm, p, CIRCUITS, true);   break;
    case ACTION_FIVE:   action_button(tm, p, CONSOLE, true);    break;
    case ACTION_SIX:    action_button(tm, p, RC2014, true);     break;
    case ACTION_SEVEN:  action_power_lock(tm, p);               break;
    case ACTION_ZERO:   
        narrate("You look away from the control panel.\n", SLOW);
        p->view = VIEW_INSIDE; p->new_view = true;              break;
    default:    check_general_actions(tm, p, input[0]);
    }
}

void view_aux_panel(struct time_machine* tm, struct player* p) {
    if (p->new_view) {
        p->new_view = false;
        narrate("\nYou are looking at the auxillary control panel.\n", NORM);
        narrate("\nThe panel, labeled 'AUXILLARY PARTS', shows the following:\n", NORM);
        narrate(panel_line, FAST);
        narrate("    |Tot. Aggro|Threat Sen|Inv Shield|Hover Prop|\n", FAST);
        narrate(panel_line2, FAST);
        snprintf(print, PRINT_BUF, "    |%3i aggro | |1| %3s  | |2| %3s  | |3| %3s  |\n",
                 // TODO: fix this
                 get_power_status(tm, SENSORS, false) ? p->aggro : -1,
                 get_power_status(tm, SENSORS, false),
                 get_power_status(tm, SHIELD, false),
                 get_power_status(tm, HOVER, false));
        narrate(print, FAST);
        narrate(panel_line, FAST);
        narrate("    |Tot.Energy|Tesla Coil|Mr. Fusion|Steam Gen.|\n", FAST);
        narrate(panel_line2, FAST);
        snprintf(print, PRINT_BUF, "    | %6ikJ | |4| %3s  | |5| %3s  | |6| %3s  |\n",
                 tm->energy, get_power_status(tm, TESLA, false),
                 get_power_status(tm, FUSION, false),        
                 get_power_status(tm, STEAM, false));
        narrate(print, FAST);
        narrate(panel_line, FAST);
        narrate("You can press one of the numbered buttons or |0| look away.\n", FAST);
    } else {
        narrate("\nYou are still looking at the auxillary control panel.\n", NORM);
    }
    delay(2048);
    input[0] = get_response();     // pull one char into the input buffer
    switch(input[0]) {
    case ACTION_ONE:    action_button(tm, p, SENSORS, false);    break;
    case ACTION_TWO:    action_button(tm, p, SHIELD, false);     break;
    case ACTION_THREE:  action_button(tm, p, HOVER, false);      break;
    case ACTION_FOUR:   action_button(tm, p, TESLA, false);      break;
    case ACTION_FIVE:   action_button(tm, p, FUSION, false);     break;
    case ACTION_ZERO:   
        narrate("You look away from the control panel.\n", NORM);
        p->view = VIEW_INSIDE; p->new_view = true;              break;
    default:    check_general_actions(tm, p, input[0]);
    }
}

/*
-------------------------------------------------------------
|   CRITICAL  PARTS    | Num./Status |   AUXILLARY  PARTS   |
-------------------------------------------------------------
| Power Distrib. Unit  | NOM |1| NOM | Threat Sensor System |
| asdfasdfasdfasdfas  | FLT ||2|| NOM | Something else       |
*/

void view_breaker_panel(struct time_machine* tm, struct player* p) {
    if (p->new_view) {
        p->new_view = false;
        narrate("\nYou are looking at the circuit breaker panel.\n", NORM);
        narrate("\nThe panel is organized into two columns of part statuses:\n", NORM);
        narrate(breaker_line, FAST);
        narrate("|   CRITICAL   PARTS   | Bank/Status |   AUXILLARY  PARTS   |\n", FAST);
        narrate(breaker_line, FAST);
        for (int i = 0; i < 6; i++) {
        snprintf(print, PRINT_BUF, "| %20s | %3s |%i| %3s | %20s |\n",
                 get_critical_part(i),
                 breaker_disp[get_critical_fault(i, tm->crit_status)], i,
                 breaker_disp[get_auxillary_fault(i, tm->aux_status)],
                 get_auxillary_part(i));
        narrate(print, FAST);
        }
        narrate(breaker_line, FAST);
        narrate("You can press one of the numbered buttons or |0| look away.\n", FAST);
    } else {
        narrate("\nYou are still looking at the circuit breaker panel.\n", NORM);
    }
    delay(2048);
    input[0] = get_response();     // pull one char into the input buffer
    switch(input[0]) {
    case ACTION_ONE:    action_button(tm, p, SENSORS, false);    break;
    case ACTION_TWO:    action_button(tm, p, SHIELD, false);     break;
    case ACTION_THREE:  action_button(tm, p, HOVER, false);      break;
    case ACTION_FOUR:   action_button(tm, p, TESLA, false);      break;
    case ACTION_FIVE:   action_button(tm, p, FUSION, false);     break;
    case ACTION_ZERO:   
        narrate("You look away from the control panel.\n", NORM);
        p->view = VIEW_INSIDE; p->new_view = true;              break;
    default:    check_general_actions(tm, p, input[0]);
    }
}

void view_computer(struct time_machine* tm, struct player* p) {
    // TODO: computer section goes here
    narrate("If there was a computer to look at, that would be nice, huh?\n", SLOW);
    delay(8192);
    p->view = VIEW_INSIDE;
}

void view_console(struct time_machine* tm, struct player* p) {
    narrate("You turn your attention to the console screen.\n", NORM);
    lineprint('_', 64);
    delay(8192);
    tdos_command_loop(tm, p);
    // TODO: time processing for post-tdos use goes here
}

void view_storage(struct time_machine* tm, struct player* p) {
    // TODO: storage compartment goes here
    p->new_view = false;
    narrate("You forgot to pay your storage bill and are locked out.\n", SLOW);
    delay(8192);
    p->view = VIEW_INSIDE;
}

void view_outside(struct time_machine* tm, struct player* p) {
    // TODO: outside loop goes here
    p->new_view = false;
    narrate("Go outside, touch grass, then come back.\n", SLOW);
    delay(8192);
    p->view = VIEW_INSIDE;
}

void view_repairs(struct time_machine* tm, struct player* p) {
    // TODO: repair loop goes here
    p->new_view = false;
    narrate("Why are you came?\n", SLOW);
    delay(8192);
    p->view = VIEW_INSIDE;
}

/***** simulator action functions *****/

void action_help(void) {
    narrate("\nTo select an action listed above, type the number in bars\n"
            "next to it (e.g. |2|) and press enter.\n", NORM);
    narrate("\nType the following letter for these general actions:\n", NORM);
    for (int i = 0; i < GEN_ACTIONS; i++) {
        narrate(general_actions[i], NORM);
    }
    delay(8192);
}

void action_pause(struct player* p) {
    narrate("Pausing the game.\n", NORM);
    p->paused = true;
}

void action_button(struct time_machine* tm, struct player* p, uint8_t part, bool is_crit) {
    char* part_name = is_crit ? get_critical_part(part) : get_auxillary_part(part);
    bool is_fault = is_crit ? get_critical_fault(part, tm->crit_status)
                            : get_auxillary_fault(part, tm->aux_status);
    bool is_on = is_crit ? get_critical_power(part, tm->crit_power)
                         : get_auxillary_power(part, tm->aux_power);
    if (is_fault) {
        snprintf(print, PRINT_BUF, "\nPressing the %s button did nothing.\n", part_name);
        narrate(print, NORM);
        narrate("It still is displaying a fault ('FLT') status.\n", NORM);
    } else if (is_on) {
        turn_off_part(part, true, tm);
        snprintf(print, PRINT_BUF, "\nAfter pressing the button, the %s turns off.\n", part_name);
        narrate(print, NORM);
        narrate("\nThe control panel lights flicker and update the display.\n", NORM);
        p->new_view = true;     // let user see refreshed panel
    } else if (turn_on_part(part, is_crit, tm)) {
        snprintf(print, PRINT_BUF, "\nAfter pressing the button, the %s turns on.\n", part_name);
        narrate(print, NORM);
    } else {
        narrate("Pressing the button caused some sparks inside.\n", SLOW);
        snprintf(print, PRINT_BUF, "The %s is now showing a fault ('FLT') status.\n", part_name);
        narrate(print, NORM);
    }
    delay(4096);
}

void action_power_lock(struct time_machine* tm, struct player* p) {
    narrate("You have no power here.\n", SLOW);
}

/***** simulator helper functions *****/

void narrate(char* str, uint8_t speed) {
    switch (speed) {
    case FAST:  tmprint(str, FAST_NARR);    return;
    case NORM:  tmprint(str, NORM_NARR);    return;
    case SLOW:  tmprint(str, SLOW_NARR);    return;
    default: printf("Something went wrong in narrate()\n");
    }
}

void check_general_actions(struct time_machine* tm, struct player* p, int response) {
    switch (toupper(response)) {
    case ACTION_HELP:   action_help();          break;
    case ACTION_LOOK:   p->new_view = true;     break;
    case ACTION_PAUSE:  action_pause(p);        break;        
    default: narrate("Input not recognized.\n", NORM);
    }
}

void check_computer(struct time_machine* tm, struct player* p) {
    if (!get_critical_power(COMPUTER, tm->crit_power)  ||
         get_critical_fault(COMPUTER, tm->crit_status) || 
        !get_critical_power(CONSOLE,  tm->crit_power)  ||
         get_critical_fault(CONSOLE,  tm->crit_status)) {
        p->view = VIEW_COMPUTER;
    } else { p-> view = VIEW_CONSOLE; }
}