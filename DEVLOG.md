# Dev Log:

## Zameen Cater

### 2024-01-03 - Wrote proposal
Wrote proposal (2 hours)

### 2024-01-04 - Keyboard input
Figured out how to accept input from keyboard and display onto terminal. (1-2 hrs)

### 2024-01-05 - Further keyboard input
Expanded keyboard input to accept multi-byte input (arrow keys, Insert, Delete, Home, End, etc) (1.5 hours)

### 2024-01-06 - ncurses replacement
Replaced all existing keyboard input code with ncurses code (2 hours)

### 2024-01-07 - refactoring and prettying
Improved general aesthetic and learned more about ncurses (1 hour)
Split program into multiple files and entirely refactored code (2 hours)
Added more key functionality and rewrote code (45 min)
Implemented half a config file (4 hours)

### 2024-01-08 - integration and file-opening
Integrated Raymond's file-reading code with the display (1 hour)
Files can now be opened by passing them as a command-line argument (15 minutes)
Added row numbers and improved config file (30 minutes)

### 2024-01-09 - better cursor behavior
The cursor can no longer freely move and instead follows a vi-esque movement style (30 minutes)

### 2024-01-11 - wrote all of the insertion code
Insertion now works like a regular text editor (20 minutes)  
Insertion and deletion of lines works as expected (2.5 hours)


## Raymond Zhang

### 2024-01-03 - Wrote proposal
Wrote proposal (2 hours)

### 2024-01-04 - Reading from file
Spent programming reading from file line by line, only got 1 line working. (45 min including class time)

### 2024-01-05 to 2024-01-07 - Reading from file
Finished implementing file reading with line numbers, through the use of double linked lists (3 hours total)

### 2024-01-08 - Saving to file pt. 1
Wrote savefile (30 min), tried to debug not printing lines correctly but to no avail (30 min)

### 2024-01-09 - Saving to file pt. 2, Saving file
Took a while debugging savefile and fixing ncurses issues (40 minutes), freedoc function (15 min), freedoc implementation (10 min)

### 2024-01-10 - Fixing spacing error, Moving code around to more reasonable areas
Debugging spacing error (20 min), moving code (10 min)

### 2024-01-11 - Extensive testing of text editor, preliminary select function written
Testing (40 min), Select function (15 min)
