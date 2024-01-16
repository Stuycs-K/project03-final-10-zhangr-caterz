# OFFICIAL GIGA HELP FILE (written using Giga, of course)

## giga v1

### created by R Zhang and Z Cater (Team Name: TEAM C[RAY]TER)

Giga, stylized as giga, is a minimalistic text editor intended to be a cross between vi's line-based approach and cute aesthetic and nano's usage of simpler-than-emacs keybinds, instead of using separate modes and recursive commands.

To compile:
0. Install libncurses5-dev using `sudo apt-get install libncurses5-dev` or an equivalent (or ask Mr K)
1. Run `make compile` while in the same directory as giga and ensure there are no errors. If there are errors, cry and do not continue.

To run:
0. While in the same directory as giga, run `./giga` to open giga with an empty buffer, or `./giga data/beemovie.txt`, for example, to open giga with a file already opened.
1. Press ^Q at any time (except during an input prompt) to quit.


---

## SHORTCUTS

- F1-F8: switch between tabs

- ^Q: quit
- ^W: write to file
- ^E: toggle edit mode between insert and replace
- ^R: revert buffer to match original file, wipe changes
- ^T: create new tab

- ^A: ascend n rows
- ^S: skip to row n
- ^D: descend n rows
- ^G: get help (switch to help tab)

- ^Z: begin selection (mark)
- ^C: copy from mark
- ^V: paste copy buffer
- ^N: paste copy buffer (for systems overriding ^V)

- Arrow keys to navigate

- Enter:     insert newline
- Tab:       insert tabsize spaces
- Backspace: delete previous character

- Delete:    delete next character
- Insert:    toggle edit mode between insert and replace
- Home:      jump to start of line
- End:       jump to end of line
- Page Up:   jump to top of screen
- Page Down: jump to bottom of screen

---

## CONFIG FILE FORMAT

Each line starts with "set" followed by an attribute.
- color: takes a window name and two colors
- bold, underline, dim, highlight: take a window name
- tabsize: takes an integer (default: 4)
- maxlength: takes an integer (default: 256)
Comments with begin with #

---

## ADDITIONAL FEATURES

- Triple dashes (---) appear as horizontal lines in giga
- Immutable files, such as the built-in helpfile tab
- Automatic adjustment on window resize
- Writing to a file will default to the current file name
- Writing a blank buffer into a file will update the tab name and default file name
- Automatic prevention of creating more than 8 tabs (+1 for the helpfile)
- ^G in the helpfile will always return to the most recent file
- Bottom-bar alerts disappear as soon as a key is pressed
- Customizable config file and help file, set to read from giga.conf and help.txt

---

## KNOWN BUGS

- Pressing End on the last line of the screen will not visually scroll the screen until another key is pressed
- Unknown and most likely unintended behavior if a line ever has more than maxlength characters
- Undefined behavior (probably an error) if an unavailable file is specified
- Pressing ^anything while in an input prompt will lock up the program indefinitely (not our problem, it's ncurses' fault--it'll never read an end-of-input and give us control back)
- Running giga while in another directory will fail
