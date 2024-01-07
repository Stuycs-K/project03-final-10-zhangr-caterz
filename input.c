#include <ncurses.h>
#include "giga.h"
#include <ctype.h> // isprint
#include "util.h" // clamp
#include "input.h"

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

void keyStuff(){
  int ch;

  while(1){
    ch = getKey();
    if(ch==KEY_UP || ch==KEY_DOWN || ch==KEY_LEFT || ch==KEY_RIGHT) moveCursor(ch);
    else if(isprint(ch)) {
      wprintw(edit_window, "%c", ch);
      E.cx++;
    }
    else wprintw(edit_window, "%d", ch);

    updateCursor();
    wrefresh(edit_window);

    if(ch==KEY_CTRL('q')) break;
  }
}
