#include <ncurses.h>
#include "giga.h"
#include <stdlib.h> // atexit
#include "config.h"
#include "read.h" // readFile
#include "modify.h" // refresh_all
#include "cursor.h" // init_cursor
#include "helpbar.h" // helpbar_default
#include "setup.h"

void reset();
void alternate(WINDOW* win, attr_t attr, char* special, char* normal);

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
  info_window = newwin(1, getmaxx(stdscr), 0, 0);
  help_window = newwin(1, getmaxx(stdscr), getmaxy(stdscr)-1, 0);
  edit_window = newwin(getmaxy(stdscr)-2, getmaxx(stdscr)-3, 1, 3);
  nums_window = newwin(getmaxy(stdscr)-2, 3, 1, 0);
  refresh();

  // initialize color pairs
  init_pair(1, COLOR_BLACK, COLOR_WHITE);
  init_pair(2, COLOR_WHITE, COLOR_BLACK);
  init_pair(3, COLOR_WHITE, COLOR_BLACK);
  init_pair(4, COLOR_WHITE, COLOR_BLACK);
  wbkgd(info_window, COLOR_PAIR(1));
  wbkgd(help_window, COLOR_PAIR(2));
  wbkgd(edit_window, COLOR_PAIR(3));
  wbkgd(nums_window, COLOR_PAIR(4));

  // use config file to modify color pairs
  readConfig();

  // initialize editor status
  E.miny = 0; E.minx = 0;
  getmaxyx(edit_window, E.height, E.width);
  E.mode = 0; // insert mode
  E.data = readFile(E.path, NULL);
  E.curr_line = E.data;
  E.first_line = E.data;

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

//runs at very end of the program, when exited or returned
void reset(){
  delwin(info_window);
  delwin(help_window);
  delwin(edit_window);
  endwin();
  free_doc(E.data);
}

void resize(){
  endwin();
  refresh();
  //doupdate();

  wresize(info_window, 1, getmaxx(stdscr));
  mvwin(help_window, getmaxy(stdscr)-1, 0);
  wresize(help_window, 1, getmaxx(stdscr));
  wresize(edit_window, getmaxy(stdscr)-2, getmaxx(stdscr)-3);
  wresize(nums_window, getmaxy(stdscr)-2, 3);
  refresh();

  E.miny = 0; E.minx = 0;
  getmaxyx(edit_window, E.height, E.width);
  E.first_line = E.curr_line;
  E.cy = 0; E.cy_old = 0;
  refresh_all();
  helpbar_alert("resized!");
  updateCursor();

  wrefresh(help_window);
  wrefresh(nums_window);
  wrefresh(info_window);
  wrefresh(edit_window);
}
