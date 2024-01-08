#include <ncurses.h>
#include "giga.h"
#include <ctype.h> // isprint
#include "setup.h" // setup
#include "cursor.h" // moveCursor, updateCursor
#include "texteditor.h" // readFile
#include "util.h" // err

struct editor_status E;
WINDOW *info_window;
WINDOW *help_window;
WINDOW *edit_window;
struct line *data;

int main(){

  setup();
  
  data = NULL;
  data = readFile("./test.txt", data);
  
  /*endwin();
  print_list(data);
  err(-1, "you're bad");*/
  
  struct line *list = data;
  int i = 0;
  while(list != NULL) {
    wmove(edit_window, i, 0);
    wprintw(edit_window, "[%d]", list->line_num);
    wprintw(edit_window, "%s", list->str);
    list = list->next;
    i++;
    wrefresh(edit_window);
  }

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
