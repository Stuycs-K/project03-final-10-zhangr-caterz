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
  wmove(edit_window, E.cy - E.miny, E.minx);
  wclrtoeol(edit_window);
  wprintw(edit_window, "%s", E.curr_line->str);
}

void refresh_all(){
  werase(nums_window);
  werase(edit_window);
  int i=0;
  for(struct line *node = E.first_line; node && i<E.height; node = node->next) {
    mvwprintw(nums_window, i, 0, "%2d", node->line_num);
    mvwprintw(edit_window, i, E.minx, "%s", node->str);
    i += node->line_len / E.width + 1;
  }
  while(i<E.height){
    mvwprintw(nums_window, i, 0, "~");
    i++;
  }
}

void init_colors(){
  init_pair(1, COLOR_BLACK, COLOR_WHITE);
  init_pair(2, COLOR_WHITE, COLOR_BLACK);
  init_pair(3, COLOR_WHITE, COLOR_BLACK);
  init_pair(4, COLOR_WHITE, COLOR_BLACK);
  wbkgd(info_window, COLOR_PAIR(1));
  wbkgd(help_window, COLOR_PAIR(2));
  wbkgd(edit_window, COLOR_PAIR(3));
  wbkgd(nums_window, COLOR_PAIR(4));
}

void resize_windows(){
  wresize(info_window, 1, getmaxx(stdscr));
  mvwin(help_window, getmaxy(stdscr)-1, 0);
  wresize(help_window, 1, getmaxx(stdscr));
  wresize(edit_window, getmaxy(stdscr)-2, getmaxx(stdscr)-3);
  wresize(nums_window, getmaxy(stdscr)-2, 3);
  refresh();
}
