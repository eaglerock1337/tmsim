# tmsim - a nominally fun time machine simulator

**nom·i·nal** /ˈnämən(ə)l/ *adj.* **1.** existing in name only.

## about

I'll tell you a story all about it later.

For now, I am documenting the [versions](./docs/VERSIONS.md) and have documented some [history](./docs/HISTORY.md).

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

## design constraints

Since this has to fit within approximatly 40K of RAM to fit on the RC2014 and work with CP/M, I am saving on memory as much as possible, including passing along game state via pointers as much as possible to avoid duplicating data in memory.

As a result, the codebase includes a lot of nonpure functions that alter game state through struct pointers. While this is one step above using global variables, it at least makes it clear what is being adjusted.

I am also heavily relying on the preprocessor to allow keeping as much data as possible within simple, one-byte variables, indexed with enumerated values for code readability.
