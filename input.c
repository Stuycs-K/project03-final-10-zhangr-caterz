#include <stdlib.h> // atexit
#include <ncurses.h> // ncurses
#include <ctype.h> // isprint

#define KEY_CTRL(c) ((c) & 0x1f)

void setup(){
  initscr();
  raw();
  keypad(stdscr, TRUE);
  noecho();
  nonl();
  curs_set(1);
}

void reset(){
  endwin();
}

int getKey(){
  int ch = getch();
  return ch;
}

int main(){

  setup();
  atexit(reset);

  int ch;

  while(1){
    ch = getKey();
    if(ch==KEY_LEFT) printw("left");
    else if(ch==KEY_RIGHT) printw("right");
    else if(ch==KEY_UP) printw("up");
    else if(ch==KEY_DOWN) printw("down");
    else if(ch==KEY_ENTER) printw("enter");
    else if(ch==KEY_CTRL('b')) printw("2");
    else if(ch==KEY_CTRL('c')) printw("3");
    else if(isprint(ch)) printw("%d: %c", ch, ch);
    else printw("%d", ch);
    printw("\n");
    refresh();

    if(ch==KEY_CTRL('q')) break;
  }

  return 0;
}
