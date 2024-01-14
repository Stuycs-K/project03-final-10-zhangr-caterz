#include <ncurses.h>
#include "giga.h"
#include "util.h" // clamp
#include "cursor.h"
#include "visual.h" // scroll_window, refresh_all
#include <limits.h> // INT_MAX

// reads character from keyboard input and moves cursor
void moveCursor(int ch){
  T.cy_old = T.cy;
  switch(ch){
    case KEY_UP:
      if(T.curr_line->previous) T.cy -= T.curr_line->previous->line_len / E.width + 1;
      break;
    case KEY_DOWN:
      T.cy += T.curr_line->line_len / E.width + 1;
      break;
    case KEY_LEFT:
      T.cx = T.cx_real - 1; break;
    case KEY_RIGHT:
      if(T.cx<T.curr_line->line_len) T.cx = T.cx_real + 1; break;
    case KEY_HOME:
      T.cx = E.minx; break;
    case KEY_END:
      T.cx = INT_MAX; break;
    case KEY_PPAGE: // page up
      T.cy = E.miny; break;
    case KEY_NPAGE: // page down
      T.cy = E.miny + E.height - 1; break;
    //case KEY_CTRL('m'): // enter, but KEY_ENTER is mapped to the numpad
    //  T.cy++; T.cx = E.minx; break;
    //case KEY_BACKSPACE:
    //  T.cx--; break;
    case KEY_STAB: // tab
      T.cx = T.cx_real;
  }
}

void updateCurrLine(){
  while(T.cy_old < T.cy){
    if(!T.curr_line->next) {T.cy = T.cy_old; break;}
    T.cy_old += T.curr_line->line_len / E.width + 1;
    T.curr_line = T.curr_line->next;
  }
  while(T.cy_old > T.cy){
    if(!T.curr_line->previous) {T.cy = T.cy_old; break;}
    T.cy_old -= T.curr_line->previous->line_len / E.width + 1;
    T.curr_line = T.curr_line->previous;
  }
}

// ensures cursor is in valid position and moves it
void updateCursor(){
  updateCurrLine();
  scroll_window();

  T.cx = MAX(T.cx, E.minx);
  T.cx_real = MIN(T.cx, T.curr_line->line_len);
  wmove(EDIT_WINDOW, T.cy - E.miny + T.cx_real / E.width, T.cx_real % E.width);
}

void init_cursor(){
  T.cx = E.minx;
  T.cy = E.miny;
  T.cx_real = T.cx;
  T.cy_old = T.cy;
  wmove(EDIT_WINDOW, T.cy - E.miny, T.cx_real);
}
