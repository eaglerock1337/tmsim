  10 REM ******* TM SIM ********
  20 REM *  By EagleRock1337   *
  30 REM *   9/6-xx/xx/2020    *
  40 REM ***********************
 100 GO SUB 1000: REM Initialize
 200 GO TO 2000: REM Main Loop
1000 REM **** Initialization ***
1010 LET comp=0
1020 LET score=12345
1030 LET day=20
1040 LET month=7
1050 LET year=1982
1300 FOR i=0 TO 16
1310 FOR j=0 TO 7 
1320 READ g
1330 POKE USR CHR$ (144+i)+j,g
1340 NEXT j
1350 NEXT i
1360 LET t$= CHR$ 144+ CHR$ 144+ CHR$ 145+ CHR$ 146
1370 FOR i=1 TO 3: LET t$=t$+ CHR$ 147: NEXT i
1380 FOR i=1 TO 16: LET t$=t$+ CHR$ 148: NEXT i
1390 FOR i=1 TO 3: LET t$=t$+ CHR$ 147: NEXT i
1400 LET t$=t$+ CHR$ 146+ CHR$ 145+ CHR$ 144+ CHR$ 144
1410 LET b$= CHR$ 144+ CHR$ 144+ CHR$ 149+ CHR$ 150
1420 FOR i=1 TO 3: LET b$=b$+ CHR$ 151: NEXT i
1430 FOR i=1 TO 16: LET b$=b$+ CHR$ 152: NEXT i
1440 FOR i=1 TO 3: LET b$=b$+ CHR$ 151: NEXT i
1450 LET b$=b$+ CHR$ 150+ CHR$ 149+ CHR$ 144+ CHR$ 144
1470 PRINT "Initialized"
1480 PRINT "Press key to continue": PAUSE 0
1490 RETURN
1500 REM **** New Game *********
1510 PRINT "New Game"
1520 GO SUB 7000: REM Intro
1530 PRINT "Press key to start": PAUSE 0
1540 GO TO 3000: REM Outside
2000 REM **** Main Menu ********
2010 CLS: BORDER 7
2015 PRINT "Time Machine Sim": PRINT
2020 PRINT "Main Menu"
2030 PRINT "1. New Game"
2040 PRINT "2. Load Game"
2050 PRINT "3. Save Game"
2060 PRINT "4. Enter Sim"
2070 PRINT "5. Watch Intro"
2080 PRINT "6. How to Play"
2090 PRINT "7. Quit TM SIM"
2100 LET i$=INKEY$
2110 IF i$="1" THEN GO TO 1500: REM New Game
2120 IF i$="2" THEN GO TO 8000: REM Load Game
2130 IF i$="3" THEN GO TO 8500: REM Save Game
2140 IF i$="4" THEN GO TO 3000: REM Enter Sim - Outside
2150 IF i$="5" THEN GO SUB 7000: REM Introduction
2160 IF i$="6" THEN GO TO 7500: REM How to Play
2170 IF i$="7" THEN GO TO 9900: REM Program Exit
2200 GO TO 2100
3000 REM **** Outside Loop *****
3010 CLS: BORDER 0
3020 PRINT "Outside Loop"
3030 PRINT "1. Enter TM"
3040 PRINT "2. Exit Sim"
3100 LET i$=INKEY$
3120 IF i$="1" THEN GO TO 4000: REM Sim - Enter TM
3130 IF i$="2" THEN GO TO 2000: REM Main Menu
3200 GO TO 3100
4000 REM **** Inside Loop ******
4010 CLS: BORDER 0
4020 PRINT "Inside Loop"
4030 IF comp=0 THEN PRINT "Computer: Off"
4040 IF comp=1 THEN PRINT "Computer: On"
4050 PRINT "1. Look at Display"
4060 PRINT "2. Exit TM"
4100 LET i$=INKEY$
4110 IF i$="1" AND comp=0 THEN GO TO 5000: REM Sim - Display
4120 IF i$="1" AND comp=1 THEN GO TO 6000: REM Sim - TDOS
4130 IF i$="2" THEN GO TO 3000: REM Sim - Outside
4200 GO TO 4100
5000 REM **** Display Loop *****
5010 CLS: BORDER 0
5020 PRINT "Display Loop"
5030 PRINT "1. Turn on computer"
5040 PRINT "2. Look away from display"
5100 LET i$=INKEY$
5110 IF i$="1" THEN GO TO 5500: REM Boot Sequence
5120 IF i$="2" THEN GO TO 4000: REM Sim - Inside
5200 GO TO 5100
5500 REM **** Boot Sequence ****
5510 CLS
5520 LET comp=1
5530 PRINT "Boot Sequence"
5540 PRINT "Press key to continue": PAUSE 0
5550 GO TO 6000: REM TDOS Loop
6000 REM **** TDOS Loop ********
6010 CLS: BORDER 0
6020 GO SUB 9500: REM header
6030 INK 7: PAPER 0
6090 PRINT AT 3,1;t$
6100 LET l$="                            "
6110 PRINT AT 4,1; CHR$ 144+l$+ CHR$ 144
6120 PRINT AT 5,1; CHR$ 153+l$+ CHR$ 157
6130 PRINT AT 6,1; CHR$ 154+l$+ CHR$ 158
6140 PRINT AT 7,1; CHR$ 155+l$+ CHR$ 159 
6150 FOR i=8 TO 15
6160 PRINT AT i,1; CHR$ 156+l$+ CHR$ 160
6170 NEXT i
6180 PRINT AT 16,1; CHR$ 155+l$+ CHR$ 159
6190 PRINT AT 17,1; CHR$ 154+l$+ CHR$ 158
6200 PRINT AT 18,1; CHR$ 153+l$+ CHR$ 157
6210 PRINT AT 19,1; CHR$ 144+l$+ CHR$ 144 
6220 PRINT AT 20,1;b$
6300 REM 30x18 16,8,2,2, 8,4,2,2
6310 INK 4
6320 PRINT AT 5,11; "TDOS Loop"
6330 PRINT AT 8,9; "1. Shut down"
6340 PRINT AT 9,9; "2. Look away"
6400 LET i$=INKEY$
6410 IF i$="1" THEN GO TO 6500: REM Shutdown Sequence
6420 IF i$="2" THEN GO TO 4000: REM Sim - Inside
6430 GO TO 6400: REM Disp. Loop
6500 REM **** Shutdown Sequence
6510 CLS
6520 LET comp=0
6530 PRINT "Shutdown Sequence"
6540 PRINT "Press key to continue": PAUSE 0
6550 GO TO 5000: REM TDOS Loop
7000 REM **** Introduction *****
7010 CLS
7020 PRINT "Introduction": PRINT
7030 PRINT "Press key to exit": PAUSE 0
7100 RETURN
7500 REM **** How-to Loop ******
7510 CLS
7520 PRINT "How to Play": PRINT
7530 PRINT "Press key to exit": PAUSE 0
7600 GO TO 2000: REM Main Menu
8000 REM **** Load Loop ********
8010 CLS
8020 PRINT "Load Game": PRINT
8030 PRINT "Press key to exit": PAUSE 0
8100 GO TO 2000: REM Main Menu
8500 REM **** Save Loop ********
8510 CLS
8520 PRINT "Save Game": PRINT
8530 PRINT "Press key to exit": PAUSE 0
8600 GO TO 2000: REM Main Menu
9000 REM **** USR Graphics *****
9010 DATA 255,255,255,255,255,255,255,255: REM A screen full
9020 DATA 255,255,255,255,255,255,255,0: REM B 7/8 screen top
9030 DATA 255,255,255,255,255,255,0,0: REM C 3/4 screen top
9040 DATA 255,255,255,255,255,0,0,0: REM D 5/8 screen top
9050 DATA 255,255,255,255,0,0,0,0: REM E 1/2 screen top
9060 DATA 0,255,255,255,255,255,255,255: REM F 7/8 screen bottom
9070 DATA 0,0,255,255,255,255,255,255: REM G 3/4 screen bottom
9080 DATA 0,0,0,255,255,255,255,255: REM H 5/8 screen bottom
9090 DATA 0,0,0,0,255,255,255,255: REM I 1/2 screen bottom
9100 DATA 254,254,254,254,254,254,254,254: REM J 7/8 screen left
9110 DATA 252,252,252,252,252,252,252,252: REM K 3/4 screen left
9120 DATA 248,248,248,248,248,248,248,248: REM L 5/8 screen left
9130 DATA 240,240,240,240,240,240,240,240: REM M 1/2 scrn right
9140 DATA 127,127,127,127,127,127,127,127: REM N 7/8 scrn right
9150 DATA 63,63,63,63,63,63,63,63: REM O 3/4 screen right
9160 DATA 31,31,31,31,31,31,31,31: REM P 5/8 screen right
9170 DATA 15,15,15,15,15,15,15,15: REM Q 1/2 screen right
9200 REM **** Program Data *****
9750 REM **** Print Header *****
9760 INK 0: PAPER 7: CLS
9770 PLOT 4,171: DRAW 247,0: DRAW 0,-167: DRAW -247,0: DRAW 0,166
9780 DRAW 246,0: DRAW 0,-165: DRAW -245,0: DRAW 0,165
9790 PLOT 5,155: DRAW 246,0: PLOT 5,154: DRAW 246,0
9800 LET d$="Date:"+STR$ month+"/"+STR$ day+"/"+STR$ year
9810 LET s$="Score:"+STR$ score
9820 PRINT AT 1,1; d$
9830 PRINT AT 1,20; s$
9890 RETURN
9900 REM **** Program Exit *****
9910 CLS
9920 PRINT "Bye!"