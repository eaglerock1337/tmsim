# tmsim - a nominally fun time machine simulator

**nom·i·nal** /ˈnämən(ə)l/ *adj.* **1.** existing in name only.

## about

I'll tell you a story all about it later.

For now, it's a game. With luck and ambition, it might be a fun one.

## architecture

> This is me trying to divide and conquer, so this might change up a bit.

The project is broken down into multiple modules, the main ones being:

- `tmsim.c`   - game loop for the main menu and its functions
- `sim.c`     - game loop for the simulator and its functions
- `tdos.c`    - game loop for the computer and its functions
- `tm.c`      - struct for time machine state
- `player.c`  - struct for player & simulation state

Additional modules support the game by providing data structures & helper functions:

- `travel.c`  - time travel routines
- `time.c`    - structs for tracking time
- `storage.c` - structs for items & inventory tracking
- `aggro.c`   - outside threats and tracking aggro
- `event.c`   - game events and outcomes
- `intro.c`   - the game introduction & dialogue
- `ending.c`  - the different game endings
- `save.c`    - file load/save routines
- `text.c`    - base-level text print routines

I'm sure I'll have some files containing the game data unless I somehow figure out how to avoid needing to store a lot of game text.
