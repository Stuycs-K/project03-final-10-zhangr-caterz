#include <ncurses.h>
#include "giga.h"
#include <stdlib.h> // atexit
#include "config.h"
#include "read.h" // readFile
#include "visual.h" // refresh_all, init_colors, redraw
#include "cursor.h" // init_cursor
#include "helpbar.h" // helpbar_default
#include "setup.h"

void reset();
void alternate(WINDOW* win, attr_t attr, char* special, char* normal);
void redraw();

void setup(){
  // low-level setup
  atexit(reset);

  // initialize ncurses
  initscr();
  start_color();
  raw();
  keypad(stdscr, TRUE);
  noecho();
  nonl();
  curs_set(2);

  // create windows
  INFO_WINDOW = newwin(0, 0, 0, 0);
  HELP_WINDOW = newwin(0, 0, getmaxy(stdscr)-1, 0);
  EDIT_WINDOW = newwin(0, 0, 1, 3);
  NUMS_WINDOW = newwin(0, 0, 1, 0);

  // initialize color pairs
  init_colors();

  // use config file to modify color pairs
  readConfig("giga.conf");

  // initialize editor status
  E.miny = 0; E.minx = 0;
  E.mode = 0; // insert mode
  E.data = readFile(E.path, NULL);
  E.curr_line = E.data;
  E.first_line = E.data;

  // initialize screen
  redraw();
}

// runs at very end of the program, when exited or returned
void reset(){
  delwin(INFO_WINDOW);
  delwin(HELP_WINDOW);
  delwin(EDIT_WINDOW);
  delwin(NUMS_WINDOW);
  endwin();
  free_doc(E.data);
}

void resize(){
  endwin();
  refresh();

  E.miny = 0; E.minx = 0;
  E.first_line = E.curr_line;

  redraw();
}

