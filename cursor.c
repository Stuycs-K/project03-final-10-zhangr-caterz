#include <ncurses.h>
#include "giga.h"
#include <ctype.h> // isprint
#include "util.h" // MIN, MAX
#include "cursor.h"
#include "visual.h" // scroll_window
#include "helpbar.h" // helpbar_input_int
#include <limits.h> // INT_MAX

// reads character from keyboard input and moves cursor
void cursor_keyhandler(int ch){
  int i;
  T.line_goal = T.curr_line->line_num;
  switch(ch){
    case KEY_UP:
      T.line_goal--;
      break;
    case KEY_DOWN:
      T.line_goal++;
      break;
    case KEY_LEFT:
      T.cx = T.cx_real - 1;
      break;
    case KEY_RIGHT:
      if(T.cx<T.curr_line->line_len) T.cx = T.cx_real + 1;
      break;
    case KEY_HOME:
      T.cx = 0;
      break;
    case KEY_END:
      T.cx = INT_MAX;
      break;
    case KEY_PPAGE: // page up
      T.line_goal = T.first_line->line_num;
      break;
    case KEY_NPAGE: // page down
      T.cy = T.miny + E.height - 1;
      break;
    case KEY_CTRL('m'): // enter
      T.line_goal++;
      T.cx = 0;
      break;
    case KEY_BACKSPACE:
      if(T.cx_real>0) T.cx = T.cx_real - 1;
      else{
        T.line_goal--;
        if(T.curr_line->previous) T.cx = T.curr_line->previous->line_len;
      }
      break;
    case KEY_DC: // delete
      T.cx = T.cx_real;
      break;
    case '\t': // tab
      T.cx = T.cx_real + E.tabsize - T.cx_real % E.tabsize;
      break;
    case KEY_CTRL('a'):
      i = helpbar_input_int("Lines to ascend: ");
      if(i != -1) T.line_goal -= 1;
      break;
    case KEY_CTRL('d'):
      i = helpbar_input_int("Lines to descend: ");
      if(i != -1) T.line_goal += 1;
      break;
    case KEY_CTRL('s'):
      i = helpbar_input_int("Line to skip to: ");
      if(i != -1) T.line_goal = i;
      break;
    default:
      if(isprint(ch)) T.cx = T.cx_real + 1;
      break;
  }
}

void updateCurrLine(){
  while(T.line_goal > T.curr_line->line_num){
    if(!T.curr_line->next) {T.line_goal = T.curr_line->line_num; break;}
    T.cy += T.curr_line->line_len / E.width + 1;
    T.curr_line = T.curr_line->next;
  }
  while(T.line_goal < T.curr_line->line_num){
    if(!T.curr_line->previous) {T.line_goal = T.curr_line->line_num; break;}
    T.cy -= T.curr_line->previous->line_len / E.width + 1;
    T.curr_line = T.curr_line->previous;
  }
}

// ensures cursor is in valid position and moves it
void updateCursor(){
  updateCurrLine();
  scroll_window();

  T.cx = MAX(T.cx, 0);
  T.cx_real = MIN(T.cx, T.curr_line->line_len);
  wmove(EDIT_WINDOW, T.cy - T.miny + T.cx_real / E.width, T.cx_real % E.width);
}

void init_cursor(struct tab_status *tab){
  tab->cx = 0;
  tab->cy = tab->miny;
  tab->cx_real = 0;
  tab->line_goal = tab->first_line->line_num;
  wmove(EDIT_WINDOW, tab->cy - tab->miny, tab->cx_real);
}
