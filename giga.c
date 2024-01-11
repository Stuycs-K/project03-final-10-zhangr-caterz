#include <ncurses.h>
#include "giga.h"
#include <ctype.h> // isprint
#include "setup.h" // setup
#include "cursor.h" // moveCursor, updateCursor
#include "util.h" // err
#include "read.h" //save_file, free_list

struct editor_status E;
WINDOW *info_window;
WINDOW *help_window;
WINDOW *edit_window;
WINDOW *nums_window;

int main(int argc, char *argv[]){

  E.path = argc>1 ? argv[1] : "data/tempfile.txt";
  
  setup();

  int ch;

  while(1){
    ch = getch();
    if(ch==KEY_CTRL('q')){
      break;
    }
    if(ch==KEY_CTRL('w')) save_file("./data/output.txt", E.data);
    if(ch==KEY_CTRL('r')) mvwprintw(help_window, 0, 60, "can't revert, sorry");

    mvwprintw(help_window, 0, 30, "Key pressed: %d   ", ch);
    wrefresh(help_window);

    moveCursor(ch);
    if(isprint(ch)) {
      wprintw(edit_window, "%c", ch);
      (E.curr_line->str)[E.cx_real] = ch;
      E.cx++;
    }
    updateCursor();
    wrefresh(edit_window);
  }

  return 0;
}
