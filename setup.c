#include <ncurses.h>
#include "giga.h"
#include <stdlib.h> // atexit
#include "config.h"
#include "read.h" // readFile
#include "visual.h" // refresh_all, init_colors, redraw
#include "cursor.h" // init_cursor
#include "helpbar.h" // helpbar_default
#include "util.h" // err
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

  // use config file to modify color pairs
  readConfig(E.config_path);

  struct tab_status *help = malloc(sizeof(struct tab_status));
  E.tabs[0] = help;
  help->mutable = 0;
  help->path = E.help_path;
  help->miny = 0;
  help->data = readFile(help->path, NULL);
  help->curr_line = help->data;
  help->first_line = help->data;
  init_cursor(help);

  // initialize tab
  struct tab_status *first = malloc(sizeof(struct tab_status));
  E.tabs[1] = first;
  first->mutable = 1;
  first->path = path;
  first->miny = 0;
  first->data = readFile(first->path, NULL);
  first->curr_line = first->data;
  first->first_line = first->data;
  init_cursor(first);


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
  for(int i=0; i<2; i++) free_doc(E.tabs[i]->data);
  for(int i=0; i<2; i++) free(E.tabs[i]);
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
