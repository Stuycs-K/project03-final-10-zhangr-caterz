#include <ncurses.h>
#include "giga.h"
#include <ctype.h> // isprint
#include "setup.h" // setup
#include "cursor.h" // moveCursor, updateCursor
#include "read.h" // readFile
#include "util.h" // err

struct editor_status E;
WINDOW *info_window;
WINDOW *help_window;
WINDOW *edit_window;
WINDOW *nums_window;
struct line *data;

int main(int argc, char *argv[]){

  E.path = argc>1 ? argv[1] : "./data/test.txt";
  data = readFile(E.path, NULL);
  E.curr_line = data;
  
  setup();
  
  struct line *list = data;
  for(int i=0; list; list = list->next) {
    mvwprintw(edit_window, i++, 0, "%s", list->str);
  }
  updateCursor();
  wrefresh(edit_window);

  int ch;

  while(1){
    ch = getch();
    if(ch==KEY_CTRL('q')) break;
    if(ch==KEY_CTRL('w')) mvwprintw(help_window, 0, 60, "can't write, sorry");
    if(ch==KEY_CTRL('r')) mvwprintw(help_window, 0, 60, "can't reset, sorry");

    mvwprintw(help_window, 0, 30, "Key pressed: %d   ", ch);
    wrefresh(help_window);

    moveCursor(ch);
    if(isprint(ch)) {
      wprintw(edit_window, "%c", ch);
      E.cx++;
    }
    updateCursor();
    wrefresh(edit_window);
  }

  return 0;
}
