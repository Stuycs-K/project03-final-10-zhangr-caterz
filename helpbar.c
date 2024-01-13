#include <ncurses.h>
#include "giga.h"
#include <string.h> // strlen

void alternate(WINDOW* win, attr_t attr, char* special, char* normal){
  wattron(win, attr);
  wprintw(win, "%s", special);
  wattroff(win, attr);
  wprintw(win, "%s", normal);
}

void helpbar_reset(){
  wmove(help_window, 0, 0);
  wclrtoeol(help_window);
}

void helpbar_input(char *prompt, char buf[], char *guess){
  helpbar_reset();
  wprintw(help_window, "%s", prompt);
  for(int i=strlen(guess)-1; i>=0; i--){
    ungetch(guess[i]);
  }
  echo();
  wgetnstr(help_window, buf, LINE_SIZE);
  noecho();
}

void helpbar_alert(char* str){
  helpbar_reset();
  wprintw(help_window, "%s", str);
}

void helpbar_default(){
  helpbar_reset();
  alternate(help_window, A_STANDOUT, "^Q", " quit");
  wmove(help_window, 0, 10);
  alternate(help_window, A_STANDOUT, "^W", " write");
  wmove(help_window, 0, 20);
  alternate(help_window, A_STANDOUT, "^R", " revert");
  wmove(help_window, 0, 30);
  alternate(help_window, A_STANDOUT, "^Z", " mark");
  wmove(help_window, 0, 40);
  alternate(help_window, A_STANDOUT, "^C", " copy");
  wmove(help_window, 0, 50);
  alternate(help_window, A_STANDOUT, "^V", " paste");
}
