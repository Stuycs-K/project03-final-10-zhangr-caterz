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
  wprintw(INFO_WINDOW, "%s", E.path);
}

void show_help(){
  struct editor_status temp = E;
  for(int i=0; i<4; i++) E.windows[i] = temp.windows[i];
  E.path = temp.help_path;
  E.miny = 0; E.minx = 0;
  E.mode = 0;
  E.data = readFile(E.path, NULL);
  E.curr_line = E.data;
  E.first_line = E.data;
  redraw();
  
  getch();

  free_doc(E.data);
  E = temp;
  refresh_all();
  infobar_default();
  wrefresh(INFO_WINDOW);
  wrefresh(NUMS_WINDOW);
  wrefresh(EDIT_WINDOW);
}
