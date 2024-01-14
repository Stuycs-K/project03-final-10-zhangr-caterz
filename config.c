#include <ncurses.h>
#include "giga.h"
#include <stdio.h> // fopen, fgets
#include <string.h> // strcmp, strsep
#include <ctype.h> // isdigit
#include "util.h" // split, remove_crlf

char *colnames[8] = {"black", "red", "green", "yellow", "blue", "magenta", "cyan", "white"};
char *winnames[4] = {"info", "help", "edit", "nums"};


short colname(char* str){
  for(int i=0; i<8; i++) if(!strcmp(str, colnames[i])) return i;
  return -1;
}

short winname(char* str){
  for(int i=0; i<4; i++) if(!strcmp(str, winnames[i])) return i;
  return -1;
}

WINDOW* winptr(char* str){
  for(int i=0; i<4; i++) if(!strcmp(str, winnames[i])) return E.windows[i];
  return NULL;
}

attr_t attrname(char* str){
  if(!strcmp(str, "reverse")) return A_REVERSE;
  if(!strcmp(str, "underline")) return A_UNDERLINE;
  if(!strcmp(str, "dim")) return A_DIM;
  if(!strcmp(str, "bold")) return A_BOLD;
  return A_NORMAL;
}

int tonum(char* str){
  int i;
  if(sscanf(str, "%d", &i)) return i;
  return -1;
}

void readConfig(char* path){
  FILE *f = fopen(path, "r");
  if(!f) return;

  char line[LINE_SIZE];
  char *args[16];

  while(fgets(line, LINE_SIZE, f)){
    char *ptr = strchr(line, '#');
    if(ptr) *ptr = '\0';
    remove_crlf(line);
    if(!line[0]) continue;

    split(line, args);

    if(!strcmp(args[0], "set")){
      if(!strcmp(args[1], "color")){
        if(winname(args[2]) != -1){
          init_pair(winname(args[2])+1, colname(args[3]), colname(args[4]));
        }
      }
      else if(!strcmp(args[1], "tabsize")){
        if(tonum(args[2]) != -1){
          E.tabsize = tonum(args[2]);
        }
      }
      else if(!strcmp(args[1], "maxlength")){
        if(tonum(args[2]) != -1){
          E.maxlength = tonum(args[2]);
        }
      }
      else if(attrname(args[1]) != -1){
        if(winptr(args[2])){
          wattron(winptr(args[2]), attrname(args[1]));
        }
      }
    }
  }

  fclose(f);
}
