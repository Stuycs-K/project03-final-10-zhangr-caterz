#include <ncurses.h> // endwin
#include <stdio.h> // fprintf
#include <stdlib.h> // exit
#include <errno.h> // errno
#include <string.h> // strerror
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
