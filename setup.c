#include <ncurses.h>
#include "giga.h"
#include <stdlib.h> // atexit
#include "config.h"
#include "read.h" // readFile
#include "visual.h" // refresh_all, init_colors, resize_windows
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
  info_window = newwin(0, 0, 0, 0);
  help_window = newwin(0, 0, getmaxy(stdscr)-1, 0);
  edit_window = newwin(0, 0, 1, 3);
  nums_window = newwin(0, 0, 1, 0);

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
  delwin(info_window);
  delwin(help_window);
  delwin(edit_window);
  delwin(nums_window);
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

void redraw(){
  resize_windows();

  getmaxyx(edit_window, E.height, E.width);

  // initialize info window
  wprintw(info_window, "%s", E.path);

  // initialize help window
  helpbar_default();

  // initialize nums and edit windows
  refresh_all();
  
  // initialize cursor
  init_cursor();

  wrefresh(info_window);
  wrefresh(help_window);
  wrefresh(nums_window);
  wrefresh(edit_window);
}
