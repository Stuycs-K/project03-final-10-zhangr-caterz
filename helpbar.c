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

void helpbar_reset(){
  wmove(HELP_WINDOW, 0, 0);
  wclrtoeol(HELP_WINDOW);
}

void helpbar_input(char *prompt, char buf[], char *guess){
  helpbar_reset();
  wprintw(HELP_WINDOW, "%s", prompt);
  for(int i=strlen(guess)-1; i>=0; i--){
    ungetch(guess[i]);
  }
  echo();
  wgetnstr(HELP_WINDOW, buf, LINE_SIZE);
  noecho();
}

void helpbar_alert(char* str){
  helpbar_reset();
  wprintw(HELP_WINDOW, "%s", str);
}

void helpbar_default(){
  helpbar_reset();
  alternate("^Q", " quit");
  wmove(HELP_WINDOW, 0, 10);
  alternate("^W", " write");
  wmove(HELP_WINDOW, 0, 20);
  alternate("^E", " mode");
  wmove(HELP_WINDOW, 0, 30);
  alternate("^R", " revert");
  wmove(HELP_WINDOW, 0, 40);
  alternate("^Z", " mark");
  wmove(HELP_WINDOW, 0, 50);
  alternate("^C", " copy");
  wmove(HELP_WINDOW, 0, 60);
  alternate("^V", " paste");
}
