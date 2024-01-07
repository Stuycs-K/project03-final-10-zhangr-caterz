#include <ncurses.h>
#include "giga.h"
#include "util.h" // clamp
#include "cursor.h"

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

