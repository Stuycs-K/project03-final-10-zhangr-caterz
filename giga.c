#include <ncurses.h>
#include "giga.h"
#include "setup.h" // setup, resize
#include "cursor.h" // cursor_keyhandler
#include "util.h" // err
#include "read.h" // readwrite_keyhandler
#include "modify.h" // modify_keyhandler
#include "helpbar.h" // helpbar_alert
#include "visual.h" // refresh_all
#include "tabs.h" // tab_keyhandler

struct editor_status E;
struct tab_status T;


int main(int argc, char *argv[]){

  E.config_path = "giga.conf";
  E.help_path = "help.txt";
  
  setup(argc>1 ? argv[1] : "");

  int ch;

  while(1){
    ch = getch();

    helpbar_default();

    if(ch==KEY_CTRL('q')){
      break;
    }
    else if(ch==KEY_RESIZE){
      resize();
    }
    else if(ch==KEY_IC || ch==KEY_CTRL('e')){
      E.mode = !E.mode;
      if(!E.mode) helpbar_alert("editor mode set to INSERT");
      else helpbar_alert("editor mode set to REPLACE");
    }
    
    readwrite_keyhandler(ch);
    tab_keyhandler(ch);
    cursor_keyhandler(ch);
    modify_keyhandler(ch);

    refresh_all();
  }

  return 0;
}
