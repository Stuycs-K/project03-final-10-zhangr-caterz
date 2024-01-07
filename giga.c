#include <ncurses.h>
#include "giga.h"
#include "setup.h" // setup
#include "input.h" // keyStuff
#include "util.h" // err

struct editor_status E;
WINDOW *info_window;
WINDOW *help_window;
WINDOW *edit_window;

int main(){

  setup();

  keyStuff();

  return 0;
}
