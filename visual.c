#include <ncurses.h>
#include "giga.h"
#include "visual.h"


void scroll_window(){
  while(E.cy > E.miny + E.height - 1){
    E.miny += E.first_line->line_len / E.width + 1;
    E.first_line = E.first_line->next;
    refresh_all();
  }
  while(E.cy < E.miny){
    E.miny -= E.first_line->previous->line_len / E.width + 1;
    E.first_line = E.first_line->previous;
    refresh_all();
  }
}

void refresh_line(){
  wmove(EDIT_WINDOW, E.cy - E.miny, E.minx);
  wclrtoeol(EDIT_WINDOW);
  wprintw(EDIT_WINDOW, "%s", E.curr_line->str);
}

void refresh_all(){
  werase(NUMS_WINDOW);
  werase(EDIT_WINDOW);
  int i=0;
  for(struct line *node = E.first_line; node && i<E.height; node = node->next) {
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
  wbkgd(INFO_WINDOW, COLOR_PAIR(1));
  wbkgd(HELP_WINDOW, COLOR_PAIR(2));
  wbkgd(EDIT_WINDOW, COLOR_PAIR(3));
  wbkgd(NUMS_WINDOW, COLOR_PAIR(4));
}

void resize_windows(){
  wresize(INFO_WINDOW, 1, getmaxx(stdscr));
  mvwin(HELP_WINDOW, getmaxy(stdscr)-1, 0);
  wresize(HELP_WINDOW, 1, getmaxx(stdscr));
  wresize(EDIT_WINDOW, getmaxy(stdscr)-2, getmaxx(stdscr)-3);
  wresize(NUMS_WINDOW, getmaxy(stdscr)-2, 3);
  refresh();
}
