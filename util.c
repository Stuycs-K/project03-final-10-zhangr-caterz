#include <ncurses.h> // endwin
#include <stdio.h> // fprintf
#include <stdlib.h> // exit
#include <errno.h> // errno
#include <string.h> // strerror, strsep
#include "util.h"

int err(int i, char* msg){
  if(i<0){
    endwin();
    fprintf(stderr, "Error: %s - %s\n", msg, strerror(errno));
    exit(1);
  }
  return i;
}

int clamp(int x, int min, int max){
  if(x < min) return min;
  if(x > max) return max;
  return x;
}

// splits `str` on spaces, destroys `str`
void split(char* str, char** args){
  while(*args++ = strsep(&str, " "));
}

void remove_crlf(char *str){
  while(*str && *str!='\r' && *str!='\n') str++;
  *str = '\0';
}
