#include <ncurses.h>
#include "giga.h"
#include <stdlib.h> // malloc
#include "read.h" // readFile
#include "cursor.h" // init_cursor
#include "visual.h" // redraw
#include "helpbar.h" // helpbar_alert
#include "util.h" // KEY_CTRL
#include "tabs.h"

void create_tab(char *path, int mutable){
  if(E.tabcount==9){
    helpbar_alert("Too many tabs!");
    return;
  }
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

void delete_tab(int which){
  struct tab_status *tab = E.tabs[which];
  free_doc(tab->data);
  free(tab);
  E.tabcount--;
  for(int i=which; i<E.tabcount; i++) E.tabs[i] = E.tabs[i+1];
}

void switch_tab(int intended){
  if(intended==E.curr_tab) return;
  if(intended>=E.tabcount){
    helpbar_alert("Not a valid tab!");
    return;
  }
  *(E.tabs[E.curr_tab]) = T;
  E.last_tab = E.curr_tab;
  E.curr_tab = intended;
  T = *(E.tabs[E.curr_tab]);
  redraw();
}

void change_tab(int ch){
  if(ch==KEY_CTRL('g')) show_help();
  else{
    for(int i=1; i<=8; i++) if(ch==KEY_F(i)) switch_tab(i);
  }
}

void show_help(){
  if(E.curr_tab) switch_tab(0);
  else switch_tab(E.last_tab);
}
