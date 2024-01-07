#include <ncurses.h>
#include "giga.h"
#include <stdio.h> // fopen, fgets
#include <string.h> // strcmp, strsep
#include "util.h" // split

void readConfig(){
  FILE *f = fopen("giga.conf", "r");
  if(!f) return;

  char line[256];
  char *args[16];

  while(fgets(line, 256, f)){
    if(line[0]=='\n' || line[0]=='#') continue;

    char *ptr = strchr(line, '#');
    if(ptr) *ptr = '\0';
    split(line, args);

    if(strcmp(args[0], "set")) continue;
    wprintw(edit_window, "[%s]", args[1]);
    wrefresh(edit_window);
  }

  fclose(f);
}
