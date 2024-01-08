#include <ncurses.h>
#include "giga.h"
#include <stdio.h> // fopen, fgets
#include <string.h> // strcmp, strsep
#include "util.h" // split

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

    if(!strcmp(args[0], "set")){
      if(!strcmp(args[1], "color")){
        if(elemname(args[2]) != -1){
          init_pair(elemname(args[2]), colname(args[3]), colname(args[4]));
        }
      }
    }
  }

  fclose(f);
}
