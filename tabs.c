#include <ncurses.h>
#include "giga.h"
#include <stdlib.h> // malloc
#include "read.h" // readFile
#include "cursor.h" // init_cursor
#include "visual.h" // redraw
#include "tabs.h"

void create_tab(char *path, int mutable){
  struct tab_status *tab = malloc(sizeof(struct tab_status));
  tab->mutable = mutable;
  tab->path = path;
  tab->miny = 0;
  tab->data = readFile(tab->path, NULL);
  tab->curr_line = tab->data;
  tab->first_line = tab->data;
  init_cursor(tab);

  E.tabs[E.tabcount] = tab;
  E.tabcount++;
}

void switch_tab(int intended){
  *(E.tabs[E.curr_tab]) = T;
  E.last_tab = E.curr_tab;
  E.curr_tab = intended;
  T = *(E.tabs[E.curr_tab]);
  redraw();
}

void show_help(){
  if(E.curr_tab) switch_tab(0);
  else switch_tab(E.last_tab);
}
