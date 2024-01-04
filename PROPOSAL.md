# Final Project Proposal


## Group Members:

Zameen Cater  
Raymond Zhang


## Intentions:

We will create a terminal-based text file editor with copy-pasting capabilities.


## Intended usage:

It will be called from the shell and run in the terminal. Users will move a cursor around using the arrow keys and will be able to perform actions such as writing to a file using special key combinations (*e.g.* with the control key, super key), inspired by the design of the `nano` text editor.
  

## Technical Details:

### Topics we will be using: 

- Working with files
- Finding information about files
- Memory allocation for the file and clipboard buffers
- Signals to deal with interrupts and kill commands
- Sockets, shared memory, and semaphores - stretch goal 2

### Project Breakdown:

- Reading file and displaying on screen (Raymond)
- Saving and closing file (Raymond)
- Dealing with keyboard input (Zameen)
- Line linked-list implementation (Zameen)
- Copy-paste functionality (Raymond and Zameen)

### Data Structures:

- a clipboard buffer (length & large `char` array (not null terminated))
- file buffer (length & linked list of lines, each a length & a `char` array)

### Algorithms:

- Determining the length of a line and how it should wrap around the screen
- Relatively logical cursor movement
- Functions relating specifically to our linked list, like combining/separating lines or pasting lines
- Character identification and printing on keypress
- Non-null-terminated buffer handling
    

## Intended pacing:

- Reading file and displaying on screen - 2024/01/05
- Saving and closing files - 2024/01/09
- Dealing with keyboard input - 2024/01/06
- Line linked-list implementation - 2024/01/09
- Saving and closing files - 2024/01/11


## Stretch goals:

1. Editing multiple lines at a time, line-based movement (vim-style)
2. Networking: multiple users can simultaneously edit a file
3. Very basic `undo` capability
