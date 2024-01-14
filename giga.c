#include <ncurses.h>
#include "giga.h"
#include <ctype.h> // isprint
#include "setup.h" // setup, resize
#include "cursor.h" // moveCursor, scrollCursor, updateCursor, init_cursor
#include "util.h" // err
#include "read.h" //save_file, free_doc
#include "modify.h" // replace, insert, delete
#include "helpbar.h" // helpbar_input, helpbar_alert
//#include "visual.h" // scroll_window, refresh_line, refresh_all

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
    else if(ch==KEY_CTRL('w')){
      char to[LINE_SIZE];
      helpbar_input("destination: ", to, E.path);
      save_file(to, E.data);
      helpbar_alert("saved!");
    }
    else if(ch==KEY_CTRL('r')){
      free_doc(E.data);
      E.data=readFile(E.path, NULL);
      E.curr_line = E.data;
      E.first_line = E.curr_line;
      init_cursor();
      refresh_all();
      helpbar_alert("reverted!");
    }
    else if(ch==KEY_CTRL('e')){
      E.mode = !E.mode;
      if(!E.mode) helpbar_alert("editor mode set to INSERT");
      else helpbar_alert("editor mode set to REPLACE");
    }
    else if(ch==KEY_RESIZE){
      resize();
    }
    else{
      helpbar_default();
      //mvwprintw(help_window, 0, 30, "Key pressed: %d   ", ch);
    }
    
    wrefresh(help_window);

    moveCursor(ch);
    //scrollCursor();

    if(isprint(ch)) {
      if(!E.mode) ins_char(E.curr_line->str, E.cx_real, ch);
      else replace(E.curr_line->str, E.cx_real, ch);
      E.cx++;
      refresh_line();
    }
    else if(ch==KEY_BACKSPACE && E.cx_real==E.minx && E.curr_line->previous){
      E.curr_line = E.curr_line->previous;
      E.cx_real = E.curr_line->line_len;
      E.cx = E.cx_real;
      del_lf(E.curr_line);
      E.cy--; E.cy_old--;
      refresh_all();
    }
    else if(ch==KEY_DC && E.cx_real==E.curr_line->line_len && E.curr_line->next){
      E.cx = E.cx_real;
      del_lf(E.curr_line);
      refresh_all();
    }
    else if(ch==KEY_BACKSPACE && E.cx_real!=E.minx){
      E.cx = E.cx_real-1;
      del_char(E.curr_line->str, E.cx_real-1);
      refresh_line();
    }
    else if(ch==KEY_DC && E.cx_real!=E.curr_line->line_len){
      del_char(E.curr_line->str, E.cx_real);
      refresh_line();
    }
    else if(ch==KEY_CTRL('m')){
      E.cx = E.minx;
      ins_lf(E.curr_line, E.cx_real);
      E.cy++;
      refresh_all();
    }
    updateCursor();
    wrefresh(nums_window);
    wrefresh(edit_window);
  }

  return 0;
}
