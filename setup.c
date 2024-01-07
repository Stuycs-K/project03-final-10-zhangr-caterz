//#include <ncurses.h>
#include "setup.h"

void alternate(WINDOW* win, attr_t attr, char* special, char* normal){
  wattron(win, attr);
  wprintw(win, "%s", special);
  wattroff(win, attr);
  wprintw(win, "%s", normal);
}

//void setup(struct editor_status *F, WINDOW* info_window, WINDOW* help_window, WINDOW* edit_window){
void setup(){
  //struct editor_status E = *F;

  // input setup
  initscr();
  raw();
  keypad(stdscr, TRUE);
  noecho();
  nonl();
  curs_set(1);

  // create windows
  info_window = newwin(1, getmaxx(stdscr)-1, 0, 0);
  help_window = newwin(1, getmaxx(stdscr), getmaxy(stdscr)-1, 0);
  edit_window = newwin(getmaxy(stdscr)-2, getmaxx(stdscr)-1, 1, 0);

  // initialize editor status
  E.miny = 0; E.minx = 0;
  getmaxyx(edit_window, E.maxy, E.maxx);

  // initialize info window
  wprintw(info_window, "NOT_A_FILE.txt");
  mvwchgat(info_window, 0, 0, -1, A_STANDOUT, 0, NULL);

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

  // initialize cursor
  E.cx = E.minx;
  E.cy = E.miny;
  wmove(edit_window, E.cy, E.cx);

  refresh();  
  wrefresh(info_window);
  wrefresh(help_window);
  wrefresh(edit_window);
}


void reset(){
  delwin(info_window);
  delwin(help_window);
  delwin(edit_window);
  endwin();
}

