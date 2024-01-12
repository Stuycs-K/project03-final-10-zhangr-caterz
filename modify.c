#include <ncurses.h>
#include "giga.h"
#include "modify.h"

void replace(char* str, int n, char ch){
  char* pos = str+n;
  *pos = ch;
}

void ins_char(char* str, int n, char ch){
  char temp;
  char* pos = str+n;
  while(*pos){
    temp = *pos;
    *pos = ch;
    ch = temp;
    pos++;
  }
  temp = *pos;
  *pos = ch;
  ch = temp;
  E.curr_line->line_len++;
}

void del_char(char* str, int n){
  char* pos = str+n;
  while(*pos){
    *pos = *(pos+1);
    pos++;
  }
}

void update(){
  wmove(edit_window, E.cy, 0);
  wclrtoeol(edit_window);
  wprintw(edit_window, "%s", E.curr_line->str);
}

