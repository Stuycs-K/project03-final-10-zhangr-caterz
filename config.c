#include <ncurses.h>
#include "giga.h"
#include <stdio.h> // fopen, fgets
#include <string.h> // strcmp, strsep
#include "util.h" // split, remove_crlf

//todo: rewrite
short colname(char* str){
  if(!strcmp(str, "black")) return 0;
  if(!strcmp(str, "red")) return 1;
  if(!strcmp(str, "green")) return 2;
  if(!strcmp(str, "yellow")) return 3;
  if(!strcmp(str, "blue")) return 4;
  if(!strcmp(str, "magenta")) return 5;
  if(!strcmp(str, "cyan")) return 6;
  if(!strcmp(str, "white")) return 7;
  return -1;
}

short elemname(char* str){
  if(!strcmp(str, "info")) return 1;
  if(!strcmp(str, "help")) return 2;
  if(!strcmp(str, "edit")) return 3;
  if(!strcmp(str, "nums")) return 4;
  return -1;
}
WINDOW* elemptr(char* str){
  if(!strcmp(str, "info")) return info_window;
  if(!strcmp(str, "help")) return help_window;
  if(!strcmp(str, "edit")) return edit_window;
  if(!strcmp(str, "nums")) return nums_window;
  return NULL;
}

attr_t attrname(char* str){
  if(!strcmp(str, "reverse")) return A_REVERSE;
  if(!strcmp(str, "underline")) return A_UNDERLINE;
  if(!strcmp(str, "dim")) return A_DIM;
  if(!strcmp(str, "bold")) return A_BOLD;
  return A_NORMAL;
}

void readConfig(){
  FILE *f = fopen("giga.conf", "r");
  if(!f) return;

  char line[256];
  char *args[16];

  while(fgets(line, 256, f)){
    char *ptr = strchr(line, '#');
    if(ptr) *ptr = '\0';
    remove_crlf(line);
    if(!line[0]) continue;

    split(line, args);

    if(!strcmp(args[0], "set")){
      if(!strcmp(args[1], "color")){
        if(elemname(args[2]) != -1){
          init_pair(elemname(args[2]), colname(args[3]), colname(args[4]));
        }
      }
      else if(attrname(args[1]) != -1){
        if(elemptr(args[2])){
          wattron(elemptr(args[2]), attrname(args[1]));
        }
      }
    }
  }

  fclose(f);
}
