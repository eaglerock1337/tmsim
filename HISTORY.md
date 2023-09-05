# tmsim history

Failure is a stepping-stone towards success. This project has failed many times before:

## circa 1999 - original time machine simulator game

- written in Pascal (Borland TurboPascal)
- uses a ridiculous amount of nested if statements
- only did basic printouts to the screen using `GotoXY()`
- attempted to look like a colored control panel
- had basic time travel, energy and charging mechanic
- I was happy I did it but never satisfied with it

## circa 2008 - first attempt of sequel time simulator

- envisioned basic game mechanics
  - time travel with date and time display
  - a more realistic HUD and mechanics
  - ability to have failures & repairs
  - different recharge methods
  - actions inside and outside the machine
- original architecture
  - original design was object-oriented
  - bash script for Linux terminals
  - written in Perl
- original attempt outcome
  - many good ideas written down
  - some object-oriented design was attempted
  - no code written - only game design notes
- failed due to getting hung up on object-oriented design
- learned the basic game I wanted to write

## Feb 2012 - second Perl-based attempt of tmsim

- same attempt as before
- ignore encapsulation and attempt a simple design
- wrote a few lines of Perl until I got hung up on screen display
- I had an idea of using a string buffer for the screen refresh routine
- the idea would have worked but I didn't trust my idea over ncurses
- failed due to not trusting the string buffer idea in the first place
- learned that a cryptic scripting language isn't the best choice
  
```perl
#!/usr/bin/perl
#
# Time Machine Sim 
#
# 0.01 Alpha
#
#

use 5.010;
use strict;
use warnings;

sub printOSscreen {

```

The entirety of my 2012 attempt at tmsim in Perl.

## Mar 2012 - attempt 3: retrying with C and ncurses

- during my Perl research, I realized ncurses would be a great display solution
- I wrote several test scrips with ncurses but didn't get far
- this attempt only was a brief idea after I got frustrated from last time
- failed due to the complexity of the research I was unboxing
- learned that ncurses isn't as hard as it first appeared

## circa 2018 - attempt 4: encapsulated with Python

- inspired after I had relearned programming using Python
- use much easier & simpler encapsulation for data structures
- use simple functions for main game routine
- started to write some data structure ideas
- introduced wear/tear part mechanic idea
- failed due to stalling on object-oriented design again
- learned that OOP isn't right for me & this game

## Sep 2020 - attempt 5: simple game loop in Sinclair BASIC

- inspired after Kickstarting the [ZX Spectrum Next](https://www.kickstarter.com/projects/spectrumnext/zx-spectrum-next-issue-2) and learning Sinclair BASIC
- based on simple BASIC game loop mechanics from game development books
- designed some ZX spectrum graphics for a basic terminal look
- basic game loop mechanic laid out
- not much else done as I realized how wasteful BASIC was
- failed due to realizing I needed to write this in Z80 assembler

```basic
  10 REM ******* TM SIM ********
  20 REM *  By EagleRock1337   *
  30 REM *   9/6-xx/xx/2020    *
  40 REM ***********************
 100 GO SUB 1000: REM Initialize
 200 GO TO 2000: REM Main Loop
```

The file header from the Sinclair BASIC attempt.

## Aug 2023 - attempt 6: vanilla C & standard library

- my current ongoing attempt
- inspired by new levels of understanding of computers
  - learned Z80 assembler and low-level programming in general
  - realized writing the program in C made the most sense
- new architecture
  - start with the simplest system & iterate outwards
  - RC2014 with simple lineprinter graphics comes first
  - ZX Spectrum graphics can then be added next with the C standard library
  - ncurses will later be added for vt100 & color support
  - finally, Cython will be introduced for further portability
- cross-compiler support:
  - z88dk compiler (Z80 CPU-based) targets:
    - RC2014
    - ZX Spectrum
    - ZX Spectrum Next
  - gcc compiler targets:
    - x86
    - x86_64
    - ARM
- planned versions
  - RC2014 version - lineprinter graphics for all systems
  - ZX Spectrum version - Spectrum graphics using C standard library
  - ZX Spectrum Next version - extended version of game w/bank-swapping
  - ncurses version - extended version using color ncurses-based graphics
  - GUI version - version using Cython-based graphics & modules
- low-level, assembly-style code
  - vanilla C will be used for the RC2014 & all Z80 targets
    - nothing but the C standard library is required at first
    - ncurses library is later needed to support Linux terminal graphics
    - *no* C++ is necessary to keep this nice and simple
  - Cython will then be introduced for wrapping the C code
    - encapsulation can then be introduced without C++ nonsense
    - Cython classes can be implemented to interface with C routines
    - this will then allow for quick addition of advanced features
    - a GUI-based and web-based games are future targets
- for the incremental work on this, see [VERSIONS.md](./VERSIONS.md)
