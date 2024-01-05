#include <unistd.h> // stdin_fileno
#include <termios.h> // terminal functions
#include <stdbool.h> // bool in_raw_mode
#include "util.h"

struct editorinfo{
  struct termios orig_termios;
  bool in_raw_mode;
};
struct editorinfo E;

// Set terminal to raw mode
void setup_terminal(){
  struct termios term;
  err(tcgetattr(STDIN_FILENO, &term), "setup tcgetattr"); 
  E.orig_termios = term;

  cfmakeraw(&term);
  err(tcsetattr(STDIN_FILENO, TCSAFLUSH, &term), "setup tcsetattr");

  E.in_raw_mode = true;
}

// Revert terminal to the original interface
void clean_terminal(){
  err(tcsetattr(STDIN_FILENO, TCSAFLUSH, &E.orig_termios), "cleaning tcsetattr");
  E.in_raw_mode = false;
}

// Read one key from stdin
char readKey(){
  char c;
  err(read(STDIN_FILENO, &c, 1), "reading keycode");
  return c;
}

void processKey(char c){
  printf("%d: %c\r\n", c, c);
  if(c==(('q') & 0x1f)){ // quit on control-q
    exit(0);
  }
}

int main(){
  setup_terminal();
  atexit(clean_terminal);
  char c;

  printf("^Q to quit\r\n");
  while(1){
    c = readKey();
    processKey(c);
  }

  return 0;
}

