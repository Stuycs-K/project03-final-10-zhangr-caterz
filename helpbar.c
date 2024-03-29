#include <ncurses.h>
#include "giga.h"
#include <string.h> // strlen

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

void helpbar_alert(char* str){
  reset_bar(HELP_WINDOW);
  wprintw(HELP_WINDOW, "%s", str);
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

int helpbar_input_int(char* prompt){
  char to[LINE_SIZE+1];
  int i;
  helpbar_input(prompt, to, "");
  if(sscanf(to, "%d", &i)) return i;
  helpbar_alert("Not a valid input!");
  return -1;
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
  wprintw(INFO_WINDOW, "Tab %d: %s", E.curr_tab, strlen(T.path) ? T.path : "no file");
  if(!T.mutable) wprintw(INFO_WINDOW, " - immutable");
}
