#include <ncurses.h>
#include "giga.h"
#include "util.h" // clamp
#include "cursor.h"

// reads character from keyboard input and moves cursor
// TODO: replace enter with line-breaking functionality
// replace backspace with deletion functionality
// make end smarter
// re-evaluate use of page up and page down
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
    case KEY_HOME:
      E.cx = E.minx; break;
    case KEY_END:
      E.cx = E.maxx; break;
    case KEY_PPAGE: // page up
      E.cy = E.miny; break;
    case KEY_NPAGE: // page down
      E.cy = E.maxy; break;
    case KEY_CTRL('m'): // enter, but KEY_ENTER is mapped to the numpad
      E.cy++; E.cx = E.minx; break;
    case KEY_BACKSPACE:
      E.cx--; break;
  }
}

// ensures cursor is in valid position and moves it
void updateCursor(){
  E.cx = clamp(E.cx, E.minx, E.maxx-1);
  E.cy = clamp(E.cy, E.miny, E.maxy-1);
  wmove(edit_window, E.cy, E.cx);
}

