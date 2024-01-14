#include <ncurses.h>
#include "giga.h"
#include "helpbar.h" // helpbar_default, infobar_default
#include "cursor.h" // init_cursor
#include "visual.h"


void scroll_window(){
  while(T.cy > E.miny + E.height - 1){
    E.miny += T.first_line->line_len / E.width + 1;
    T.first_line = T.first_line->next;
    refresh_all();
  }
  while(T.cy < E.miny){
    E.miny -= T.first_line->previous->line_len / E.width + 1;
    T.first_line = T.first_line->previous;
    refresh_all();
  }
}

void refresh_line(){
  wmove(EDIT_WINDOW, T.cy - E.miny, E.minx);
  wclrtoeol(EDIT_WINDOW);
  wprintw(EDIT_WINDOW, "%s", T.curr_line->str);
}

void refresh_all(){
  werase(NUMS_WINDOW);
  werase(EDIT_WINDOW);
  int i=0;
  for(struct line *node = T.first_line; node && i<E.height; node = node->next) {
    mvwprintw(NUMS_WINDOW, i, 0, "%2d", node->line_num);
    mvwprintw(EDIT_WINDOW, i, E.minx, "%s", node->str);
    i += node->line_len / E.width + 1;
  }
  while(i<E.height){
    mvwprintw(NUMS_WINDOW, i, 0, "~");
    i++;
  }
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
}

void redraw(){
  resize_windows();

  getmaxyx(EDIT_WINDOW, E.height, E.width);

  // initialize info window
  infobar_default();

  // initialize help window
  helpbar_default();

  // initialize nums and edit windows
  refresh_all();
  
  // initialize cursor
  init_cursor();

  wrefresh(INFO_WINDOW);
  wrefresh(HELP_WINDOW);
  wrefresh(NUMS_WINDOW);
  wrefresh(EDIT_WINDOW);
}
