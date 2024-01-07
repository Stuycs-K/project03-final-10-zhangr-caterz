#include <ncurses.h>
#include "giga.h"
#include "setup.h"
#include "input.h"
#include "util.h"


struct editor_status E;
WINDOW *info_window;
WINDOW *help_window;
WINDOW *edit_window;

int main(){

  //setup(&E, info_window, help_window, edit_window);
  setup();
  atexit(reset);

  keyStuff();

  return 0;
}
