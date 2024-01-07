#include <ncurses.h>
#include "giga.h"
#include <ctype.h> // isprint
#include "setup.h" // setup
#include "cursor.h" // moveCursor, updateCursor
#include "util.h" // err

struct editor_status E;
WINDOW *info_window;
WINDOW *help_window;
WINDOW *edit_window;

int main(){

  setup();

  int ch;

  while(1){
    ch = getch();
    mvwprintw(help_window, 0, 30, "Key pressed: %d   ", ch);
    wrefresh(help_window);

    moveCursor(ch);
    if(isprint(ch)) {
      wprintw(edit_window, "%c", ch);
      E.cx++;
    }
    updateCursor();
    wrefresh(edit_window);

    if(ch==KEY_CTRL('q')) break;
  }

  return 0;
}
