#include <ncurses.h>
#include "giga.h"
#include <string.h> // strlen
#include "read.h" // readFile, free_doc
#include "visual.h" // refresh_all
//#include "cursor.h" // init_cursor
#include "setup.h" // redraw

void alternate(char* special, char* normal){
  WINDOW *win = HELP_WINDOW;
  attr_t attr = A_STANDOUT;
  wattron(win, attr);
  wprintw(win, "%s", special);
  wattroff(win, attr);
  wprintw(win, "%s", normal);
}

void reset_bar(WINDOW* win){
  wmove(win, 0, 0);
  wclrtoeol(win);
}

void helpbar_input(char *prompt, char buf[], char *guess){
  reset_bar(HELP_WINDOW);
  wprintw(HELP_WINDOW, "%s", prompt);
  for(int i=strlen(guess)-1; i>=0; i--){
    ungetch(guess[i]);
  }
  echo();
  wgetnstr(HELP_WINDOW, buf, LINE_SIZE);
  noecho();
}

void helpbar_alert(char* str){
  reset_bar(HELP_WINDOW);
  wprintw(HELP_WINDOW, "%s", str);
}

void helpbar_default(){
  reset_bar(HELP_WINDOW);
  alternate("^Q", " quit");
  wmove(HELP_WINDOW, 0, 10);
  alternate("^W", " write");
  wmove(HELP_WINDOW, 0, 20);
  alternate("^G", " help");
}
void infobar_default(){
  reset_bar(INFO_WINDOW);
  wprintw(INFO_WINDOW, "%s", T.path);
}

void show_help(){
  *(E.tabs[E.curr_tab]) = T;
  if(E.curr_tab){
    E.last_tab = E.curr_tab;
    E.curr_tab = 0;
  }
  else{
    E.curr_tab = E.last_tab;
    E.last_tab = 0;
  }
  T = *(E.tabs[E.curr_tab]);
  redraw();
}
