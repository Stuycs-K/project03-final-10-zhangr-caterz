#include <ncurses.h>
#include "giga.h"
#include <stdlib.h> // atexit
#include "config.h"
#include "read.h" // free_doc
#include "visual.h" // init_colors, redraw
#include "util.h" // err
#include "tabs.h" // create_tab
#include "setup.h"

void reset();
void alternate(WINDOW* win, attr_t attr, char* special, char* normal);
void redraw();

void setup(char *path){
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

  // initialize editor status
  E.mode = 0; // insert mode
  E.tabsize = 4;
  E.maxlength = 256;
  E.curr_tab = 1;
  E.last_tab = 0;
  E.tabcount = 0;

  // use config file to modify color pairs
  readConfig(E.config_path);

  // initialize tabs
  create_tab(E.help_path, 0);
  create_tab(path, 1);

  T = *(E.tabs[E.curr_tab]);

  // initialize screen
  resize_windows();
  redraw();
}

// runs at very end of the program, when exited or returned
void reset(){
  delwin(INFO_WINDOW);
  delwin(HELP_WINDOW);
  delwin(EDIT_WINDOW);
  delwin(NUMS_WINDOW);
  endwin();
  for(int i=0; i<E.tabcount; i++) delete_tab(i);
}

void resize(){
  endwin();
  refresh();

  T.cy = T.miny;
  T.cy_old = T.miny;
  T.first_line = T.curr_line;

  resize_windows();
  redraw();
}
