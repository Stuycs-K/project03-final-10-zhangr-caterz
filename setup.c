#include <ncurses.h>
#include "giga.h"
#include <stdlib.h> // atexit
#include "config.h"
#include "setup.h"

void reset();
void alternate(WINDOW* win, attr_t attr, char* special, char* normal);

void setup(){
  atexit(reset);

  // input setup
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
  wbkgd(info_window, COLOR_PAIR(1));
  init_pair(2, COLOR_WHITE, COLOR_BLACK);
  wbkgd(help_window, COLOR_PAIR(2));
  init_pair(3, COLOR_WHITE, COLOR_BLACK);
  wbkgd(edit_window, COLOR_PAIR(3));
  init_pair(4, COLOR_WHITE, COLOR_BLACK);
  wbkgd(nums_window, COLOR_PAIR(4));

  // use config file to modify color pairs
  readConfig();

  // initialize editor status
  E.miny = 0; E.minx = 0;
  getmaxyx(edit_window, E.maxy, E.maxx);

  // initialize info window
  wprintw(info_window, "%s", E.path);

  // initialize help window
  alternate(help_window, A_STANDOUT, "^Q", " quit");
  wmove(help_window, 0, 10);
  alternate(help_window, A_STANDOUT, "^W", " write");
  wmove(help_window, 0, 20);
  alternate(help_window, A_STANDOUT, "^R", " reset");

  // initialize edit window
  for(int i=E.miny; i<E.maxy; i++){
    mvwaddch(edit_window, i, 0, '~');
  }

  // initialize nums window
  for(int i=E.miny; i<E.maxy; i++){
    mvwprintw(nums_window, i, 0, "%2d", i);
  }

  // initialize cursor
  E.cx = E.minx;
  E.cy = E.miny;
  wmove(edit_window, E.cy, E.cx);

  wrefresh(info_window);
  wrefresh(help_window);
  wrefresh(edit_window);
  wrefresh(nums_window);

}


void reset(){
  delwin(info_window);
  delwin(help_window);
  delwin(edit_window);
  endwin();
}

void alternate(WINDOW* win, attr_t attr, char* special, char* normal){
  wattron(win, attr);
  wprintw(win, "%s", special);
  wattroff(win, attr);
  wprintw(win, "%s", normal);
}
