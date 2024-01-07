#include <stdlib.h> // atexit
#include <ncurses.h> // ncurses
#include <ctype.h> // isprint
#include "util.h" // clamp

#define KEY_CTRL(c) ((c) & 0x1f)

struct editor_status{
  int maxx, maxy, minx, miny;
  int cx, cy;
};

struct editor_status E;
WINDOW *info_window;
WINDOW *help_window;

void setup(){
  // input setup
  initscr();
  raw();
  keypad(stdscr, TRUE);
  noecho();
  nonl();
  curs_set(1);

  // initialize editor status
  getmaxyx(stdscr, E.maxy, E.maxx);
  E.minx = 0; E.miny = 1;
  E.maxy--; E.maxy--;


  // initialize info window
  info_window = newwin(1, getmaxx(stdscr)-1, 0, 0);
  refresh();
  mvwprintw(info_window, 0, 0, "FILE NAME GOES HERE");
  wrefresh(info_window);

  // initialize help window
  help_window = newwin(1, getmaxx(stdscr), getmaxy(stdscr)-1, 0);
  refresh();
  mvwprintw(help_window, 0, 0, "^Q: quit");
  wrefresh(help_window);

  // initialize cursor
  E.cx = E.minx;
  E.cy = E.miny;
  wmove(stdscr, E.cy, E.cx);
}

void reset(){
  delwin(info_window);
  delwin(help_window);
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
  E.cx = clamp(E.cx, E.minx, E.maxx);
  E.cy = clamp(E.cy, E.miny, E.maxy);
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
    wrefresh(stdscr);

    if(ch==KEY_CTRL('q')) break;
  }

  return 0;
}
