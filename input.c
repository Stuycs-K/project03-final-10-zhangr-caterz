#include <stdlib.h> // atexit
#include <ncurses.h> // ncurses
#include <ctype.h> // isprint
#include "util.h" // clamp

#define KEY_CTRL(c) ((c) & 0x1f)

struct editor_status{
  int rows, cols;
  int cx, cy;
};

struct editor_status E;

void setup(){
  initscr();
  raw();
  keypad(stdscr, TRUE);
  noecho();
  nonl();
  curs_set(1);

  getmaxyx(stdscr, E.rows, E.cols);
  E.cx = 0;
  E.cy = 0;
}

void reset(){
  endwin();
}

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
  E.cx = clamp(E.cx, 0, E.cols);
  E.cy = clamp(E.cy, 0, E.rows);
  move(E.cy, E.cx);
}

int main(){

  setup();
  atexit(reset);

  int ch;

  while(1){
    ch = getKey();
    if(ch==KEY_UP || ch==KEY_DOWN || ch==KEY_LEFT || ch==KEY_RIGHT) moveCursor(ch);
    else if(isprint(ch)) {printw("%c", ch); E.cx++;}
    else printw("%d", ch);

    updateCursor();
    refresh();

    if(ch==KEY_CTRL('q')) break;
  }

  return 0;
}
