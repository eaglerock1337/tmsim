#include "player.h"
#include "sim.h"
#include "tm.h"

/**********************************************************
* TMSim - a nominally fun time-travelling simulator
*             by Peter Marks
*
* nom·i·nal adj. existing in name only.
*
**********************************************************/

int main (void) {
    uint8_t difficulty = 5;
    struct player me;
    struct time_machine tm;
#ifdef DEBUG
    narrate("Running tmsim in debug mode.\n", NORM);
#endif
    initialize_player(difficulty, &me);
    initialize_tm(difficulty, &tm);
    reset_part(HOVER, false, false, &tm);
    enter_sim_loop(&tm, &me);
    return 0;
}
