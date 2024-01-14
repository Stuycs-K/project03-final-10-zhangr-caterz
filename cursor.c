#include <ncurses.h>
#include "giga.h"
#include "util.h" // clamp
#include "cursor.h"
#include "visual.h" // scroll_window, refresh_all
#include <limits.h> // INT_MAX

// reads character from keyboard input and moves cursor
void moveCursor(int ch){
  E.cy_old = E.cy;
  switch(ch){
    case KEY_UP:
      if(E.curr_line->previous) E.cy -= E.curr_line->previous->line_len / E.width + 1;
      break;
    case KEY_DOWN:
      E.cy += E.curr_line->line_len / E.width + 1;
      break;
    case KEY_LEFT:
      E.cx = E.cx_real - 1; break;
    case KEY_RIGHT:
      if(E.cx<E.curr_line->line_len) E.cx = E.cx_real + 1; break;
    case KEY_HOME:
      E.cx = E.minx; break;
    case KEY_END:
      E.cx = INT_MAX; break;
    case KEY_PPAGE: // page up
      E.cy = E.miny; break;
    case KEY_NPAGE: // page down
      E.cy = E.miny + E.height - 1; break;
    //case KEY_CTRL('m'): // enter, but KEY_ENTER is mapped to the numpad
    //  E.cy++; E.cx = E.minx; break;
    //case KEY_BACKSPACE:
    //  E.cx--; break;
  }
}

void updateCurrLine(){
  while(E.cy_old < E.cy){
    if(!E.curr_line->next) {E.cy = E.cy_old; break;}
    E.cy_old += E.curr_line->line_len / E.width + 1;
    E.curr_line = E.curr_line->next;
  }
  while(E.cy_old > E.cy){
    if(!E.curr_line->previous) {E.cy = E.cy_old; break;}
    E.cy_old -= E.curr_line->previous->line_len / E.width + 1;
    E.curr_line = E.curr_line->previous;
  }
}

// ensures cursor is in valid position and moves it
void updateCursor(){
  updateCurrLine();
  scroll_window();

  E.cx = MAX(E.cx, E.minx);
  E.cx_real = MIN(E.cx, E.curr_line->line_len);
  wmove(edit_window, E.cy - E.miny + E.cx_real / E.width, E.cx_real % E.width);
}

void init_cursor(){
  E.cx = E.minx;
  E.cy = E.miny;
  E.cx_real = E.cx;
  E.cy_old = E.cy;
  wmove(edit_window, E.cy - E.miny, E.cx_real);
}
