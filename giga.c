#include <ncurses.h>
#include "giga.h"
#include <ctype.h> // isprint
#include "setup.h" // setup, resize
#include "cursor.h" // moveCursor, updateCursor, init_cursor
#include "util.h" // err
#include "read.h" // save_file, free_doc
#include "modify.h" // replace, insert, delete
#include "helpbar.h" // helpbar_input, helpbar_alert, show_help
#include "visual.h" // scroll_window, refresh_line, refresh_all

struct editor_status E;
struct tab_status T;


int main(int argc, char *argv[]){

  T.path = argc>1 ? argv[1] : "data/tempfile.txt";
  E.config_path = "giga.conf";
  E.help_path = "help.txt";
  
  setup();

  int ch;

  while(1){
    ch = getch();


    if(ch==KEY_CTRL('q')){
      break;
    }
    else if(ch==KEY_CTRL('w')){
      char to[LINE_SIZE];
      helpbar_input("destination: ", to, T.path);
      save_file(to, T.data);
      helpbar_alert("saved!");
    }
    else if(ch==KEY_CTRL('G')){
      show_help();
    }
    else if(ch==KEY_CTRL('r')){
      free_doc(T.data);
      T.data=readFile(T.path, NULL);
      T.curr_line = T.data;
      T.first_line = T.curr_line;
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
    }
    
    moveCursor(ch);

    if(isprint(ch)) {
      if(!E.mode) ins_char(T.curr_line->str, T.cx_real, ch);
      else replace(T.curr_line->str, T.cx_real, ch);
      T.cx++;
      refresh_line();
    }
    else if(ch=='\t'){
      int old=T.cx;
      while(T.cx / E.tabsize != old / E.tabsize + 1){
        if(!E.mode) ins_char(T.curr_line->str, T.cx, ' ');
        T.cx++;
      }
      refresh_line();
    }
    else if(ch==KEY_BACKSPACE && T.cx_real==E.minx && T.curr_line->previous){
      T.curr_line = T.curr_line->previous;
      T.cx_real = T.curr_line->line_len;
      T.cx = T.cx_real;
      del_lf(T.curr_line);
      T.cy--; T.cy_old--;
      refresh_all();
    }
    else if(ch==KEY_DC && T.cx_real==T.curr_line->line_len && T.curr_line->next){
      T.cx = T.cx_real;
      del_lf(T.curr_line);
      refresh_all();
    }
    else if(ch==KEY_BACKSPACE && T.cx_real!=E.minx){
      T.cx = T.cx_real-1;
      del_char(T.curr_line->str, T.cx_real-1);
      refresh_line();
    }
    else if(ch==KEY_DC && T.cx_real!=T.curr_line->line_len){
      del_char(T.curr_line->str, T.cx_real);
      refresh_line();
    }
    else if(ch==KEY_CTRL('m')){
      T.cx = E.minx;
      ins_lf(T.curr_line, T.cx_real);
      T.cy++;
      refresh_all();
    }

    updateCursor();
    wrefresh(HELP_WINDOW);
    wrefresh(NUMS_WINDOW);
    wrefresh(EDIT_WINDOW);
  }

  return 0;
}
