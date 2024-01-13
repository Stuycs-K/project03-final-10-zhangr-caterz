#include <ncurses.h>
#include "giga.h"
#include "util.h" // clamp
#include "cursor.h"
#include "modify.h" // refreshall
#include <string.h> // strlen

// reads character from keyboard input and moves cursor
// TODO: replace enter with line-breaking functionality
// replace backspace with deletion functionality
// make end smarter
// re-evaluate use of page up and page down
void moveCursor(int ch){
  E.cy_old = E.cy;
  switch(ch){
    case KEY_UP:
      if(E.curr_line->previous) E.cy -= strlen(E.curr_line->previous->str) / E.maxx + 1;
      break;
    case KEY_DOWN:
      E.cy += strlen(E.curr_line->str) / E.maxx + 1;
      break;
    case KEY_LEFT:
      E.cx = E.cx_real - 1; break;
    case KEY_RIGHT:
      E.cx = E.cx_real + 1; break;
    case KEY_HOME:
      E.cx = E.minx; break;
    case KEY_END:
      E.cx = E.maxx; break;
    case KEY_PPAGE: // page up
      E.cy = E.miny; break;
    case KEY_NPAGE: // page down
      E.cy = E.maxy; break;
    //case KEY_CTRL('m'): // enter, but KEY_ENTER is mapped to the numpad
    //  E.cy++; E.cx = E.minx; break;
    //case KEY_BACKSPACE:
    //  E.cx--; break;
  }
}

// ensures cursor is in valid position and moves it
// improve this. a lot.
// minor bug: hitting right arrow at the end of a line will move the desired cursor position, which is annoying when moving vertically (can either go straight or shift right)
void updateCursor(){
  while(E.cy_old < E.cy){
    if(!E.curr_line->next) {E.cy = E.cy_old; break;}
    E.cy_old += strlen(E.curr_line->str) / E.maxx + 1;
    E.curr_line = E.curr_line->next;
  }
  while(E.cy_old > E.cy){
    if(!E.curr_line->previous) {E.cy = E.cy_old; break;}
    E.cy_old -= strlen(E.curr_line->previous->str) / E.maxx + 1;
    E.curr_line = E.curr_line->previous;
  }

  if(E.cy==E.miny && E.first_line->previous){
    E.cy += strlen(E.first_line->previous->str) / E.maxx + 1;
    E.cy_old = E.cy;
    E.first_line = E.first_line->previous;
    refresh_all();
  }
  if(E.cy>=E.maxy-(strlen(E.curr_line->str) / E.maxx + 1) && E.first_line->next){
    E.cy -= strlen(E.first_line->str) / E.maxx + 1;
    E.cy_old = E.cy;
    E.first_line = E.first_line->next;
    refresh_all();
  }

  E.cx = MAX(E.cx, E.minx);
  E.cx_real = MIN(E.cx, E.curr_line->line_len);
  wmove(edit_window, E.cy + E.cx_real / E.maxx, E.cx_real % E.maxx);
}

void init_cursor(){
  E.cx = E.minx;
  E.cy = E.miny;
  E.cx_real = E.cx;
  E.cy_old = E.cy;
  wmove(edit_window, E.cy, E.cx_real);
}
