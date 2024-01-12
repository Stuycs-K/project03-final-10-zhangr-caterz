#include <ncurses.h>
#include "giga.h"
#include "util.h" // err
#include "modify.h"

void replace(char* str, int n, char ch){
  char* pos = str+n;
  *pos = ch;
}

void insert(char* str, int n, char ch){
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


