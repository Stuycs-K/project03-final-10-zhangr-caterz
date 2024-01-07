#include <stdlib.h> // atexit
#include <ncurses.h> // ncurses
#include <ctype.h> // isprint
#include "setup.h" // setup
#include "util.h" // clamp, editor_status
#include "giga.h"
#include <error.h>

#define KEY_CTRL(c) ((c) & 0x1f)



int getKey(){
  int ch = getch();
  return ch;
}

void moveCursor(int ch){
  switch(ch){
    case KEY_UP:
      E.cy--; break;
    case KEY_DOWN:
      E.cy++; break;
    case KEY_LEFT:
      E.cx--; break;
    case KEY_RIGHT:
      E.cx++; break;
  }
}

void updateCursor(){
  E.cx = clamp(E.cx, E.minx, E.maxx-1);
  E.cy = clamp(E.cy, E.miny, E.maxy-1);
  wmove(edit_window, E.cy, E.cx);
}

//void reset(WINDOW* info_window, WINDOW* help_window, WINDOW* edit_window){

void keyStuff(){
  int ch;

  //endwin();
  //printf("%d", E.maxy);
  //exit(1);

  while(1){
    ch = getKey();
    if(ch==KEY_UP || ch==KEY_DOWN || ch==KEY_LEFT || ch==KEY_RIGHT) moveCursor(ch);
    else if(isprint(ch)) {wprintw(edit_window, "%c", ch); E.cx++;}
    else wprintw(edit_window, "%d", ch);

    updateCursor();
    wrefresh(edit_window);

    if(ch==KEY_CTRL('q')) break;
  }
}
