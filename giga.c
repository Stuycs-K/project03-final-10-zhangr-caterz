#include <ncurses.h>
#include "giga.h"
#include <ctype.h> // isprint
#include "setup.h" // setup
#include "cursor.h" // moveCursor, updateCursor
#include "util.h" // err
#include "read.h" //save_file, free_list
#include "modify.h" // replace, insert, delete

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
      //replace(E.curr_line->str, E.cx_real, ch); // replace
      ins_char(E.curr_line->str, E.cx_real, ch); // insert
      E.cx++;
      update();
    }
    if(ch==KEY_BACKSPACE){
      del_char(E.curr_line->str, MAX(0, E.cx_real-1));
      update();
    }
    if(ch==KEY_DC){
      del_char(E.curr_line->str, E.cx_real);
      update();
    }
    updateCursor();
    wrefresh(edit_window);
  }

  return 0;
}
