#include <ncurses.h>
#include "giga.h"
#include <string.h> // strcmp
#include "helpbar.h" // helpbar_default, infobar_default
#include "cursor.h" // updateCursor
#include "util.h" // err
#include "visual.h"


void scroll_window(){
  while(T.cy > T.miny + E.height - 1){
    T.miny += T.first_line->line_len / E.width + 1;
    T.first_line = T.first_line->next;
  }
  while(T.cy < T.miny){
    T.miny -= T.first_line->previous->line_len / E.width + 1;
    T.first_line = T.first_line->previous;
  }
}

void print(char* str){
  if(!strcmp(str, "---")) whline(EDIT_WINDOW, ACS_HLINE, E.width);
  else wprintw(EDIT_WINDOW, "%s", str);
}

/*void refresh_line(){
  wmove(EDIT_WINDOW, T.cy - T.miny, 0);
  wclrtoeol(EDIT_WINDOW);
  print(T.curr_line->str);
}*/

void refresh_all(){
  updateCursor();

  werase(NUMS_WINDOW);
  werase(EDIT_WINDOW);
  int i=0;
  for(struct line *node = T.first_line; node && i<E.height; node = node->next) {
    mvwprintw(NUMS_WINDOW, i, 0, "%2d", node->line_num);
    wmove(EDIT_WINDOW, i, 0);
    print(node->str);
    i += node->line_len / E.width + 1;
  }
  while(i<E.height){
    mvwprintw(NUMS_WINDOW, i, 0, "~");
    i++;
  }

  updateCursor();

  wrefresh(INFO_WINDOW);
  wrefresh(HELP_WINDOW);
  wrefresh(NUMS_WINDOW);
  wrefresh(EDIT_WINDOW);
}

void init_colors(){
  init_pair(1, COLOR_BLACK, COLOR_WHITE);
  init_pair(2, COLOR_WHITE, COLOR_BLACK);
  init_pair(3, COLOR_WHITE, COLOR_BLACK);
  init_pair(4, COLOR_WHITE, COLOR_BLACK);
  for(int i=0; i<4; i++) wbkgd(E.windows[i], COLOR_PAIR(i+1));
}

void resize_windows(){
  wresize(INFO_WINDOW, 1, getmaxx(stdscr));
  mvwin(HELP_WINDOW, getmaxy(stdscr)-1, 0);
  wresize(HELP_WINDOW, 1, getmaxx(stdscr));
  wresize(EDIT_WINDOW, getmaxy(stdscr)-2, getmaxx(stdscr)-3);
  wresize(NUMS_WINDOW, getmaxy(stdscr)-2, 3);
  refresh();
  getmaxyx(EDIT_WINDOW, E.height, E.width);
}

void redraw(){
  // initialize info window
  infobar_default();

  // initialize help window
  helpbar_default();

  // initialize nums and edit windows
  refresh_all();
  
}
