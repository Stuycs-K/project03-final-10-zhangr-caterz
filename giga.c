#include <ncurses.h>
#include "giga.h"
#include <ctype.h> // isprint
#include "setup.h" // setup, resize
#include "cursor.h" // moveCursor, updateCursor, init_cursor
#include "util.h" // err
#include "read.h" // save_file, free_doc
#include "modify.h" // replace, insert, delete
#include "helpbar.h" // helpbar_input, helpbar_alert
#include "visual.h" // scroll_window, refresh_line, refresh_all
#include "tabs.h" // switch_tab, show_help
#include "copypaste.h"

struct editor_status E;
struct tab_status T;


int main(int argc, char *argv[]){

  E.config_path = "giga.conf";
  E.help_path = "help.txt";
  
  setup(argc>1 ? argv[1] : NULL);

  int ch;

  while(1){
    ch = getch();


    if(ch==KEY_CTRL('q')){
      break;
    }
    else if(ch==KEY_CTRL('w')){
      char to[LINE_SIZE];
      helpbar_input("destination: ", to, T.path ? T.path : "");
      save_file(to, T.data);
      helpbar_alert("saved!");
    }
    else if(ch==KEY_CTRL('r')){
      free_doc(T.data);
      T.data=readFile(T.path, NULL);
      T.curr_line = T.data;
      T.first_line = T.curr_line;
      init_cursor(&T);
      refresh_all();
      helpbar_alert("reverted!");
    }
    else if(ch==KEY_IC || ch==KEY_CTRL('e')){
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
    
    change_tab(ch);
    moveCursor(ch);
    int isMarked = 0; //0 = false, 1 = true (checks if marked)
    int * marked; = malloc(sizeof(int) * 2);
    char buffer[LINE_SIZE];
    //wprintw(HELP_WINDOW, "%d %d %d %d", ch, );

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
    else if(ch==KEY_BACKSPACE && T.cx_real==0 && T.curr_line->previous){
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
    else if(ch==KEY_BACKSPACE && T.cx_real>0){
      T.cx = T.cx_real-1;
      del_char(T.curr_line->str, T.cx_real-1);
      refresh_line();
    }
    else if(ch==KEY_DC && T.cx_real!=T.curr_line->line_len){
      del_char(T.curr_line->str, T.cx_real);
      refresh_line();
    }
    else if(ch==KEY_CTRL('m')){
      T.cx = 0;
      ins_lf(T.curr_line, T.cx_real);
      T.cy++;
      refresh_all();
    }
    else if(ch==KEY_CTRL('z') && isMarked){
      marked = mark(T.cx_real, T.cy);
      isMarked = 1;
    }
    else if(ch==KEY_CTRL('c') && !isMarked){
      strcpy(buffer, copy_text(marked, T.cx_real, T.cy));
      isMarked = 0;
    }
    else if(ch==KEY_CTRL('v') && ){
      paste_text(buffer);
    }

    
    updateCursor();
    wrefresh(HELP_WINDOW);
    wrefresh(NUMS_WINDOW);
    wrefresh(EDIT_WINDOW);
  }

  return 0;
}
