#include <unistd.h> // stdin_fileno
#include <termios.h> // terminal functions
#include <stdbool.h> // bool in_raw_mode
#include <ctype.h> // isdigit
#include "util.h"
#include "input.h"

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
// works for all except escape (waits for another character and treats it like a keycode)
int readKey(){
  char c, d, e, f;
  err(read(STDIN_FILENO, &c, 1), "reading keycode");

  if(c=='\x1b'){ // c is 
    read(STDIN_FILENO, &d, 1);
    if(d=='['){ // input is [x
      read(STDIN_FILENO, &e, 1);
      if(e=='A') return ARROW_UP;
      if(e=='B') return ARROW_DOWN;
      if(e=='C') return ARROW_RIGHT;
      if(e=='D') return ARROW_LEFT;
      if(e=='H') return HOME;
      if(e=='F') return END;
      if('0'<=e && e<='9'){ // input is [x~
        read(STDIN_FILENO, &f, 1);
        if(f=='~'){
          if(e=='2') return INSERT;
          if(e=='3') return DELETE;
          if(e=='5') return PAGE_UP;
          if(e=='6') return PAGE_DOWN;
        }
      }
    }
  }



  return c;
}

void processKey(int c){
  if(isprint(c)) printf("%d: %c\r\n", c, c);
  else           printf("%d\r\n", c);
  if(c==(('q') & 0x1f)){ // quit on control-q
    exit(0);
  }
}

int main(){
  setup_terminal();
  atexit(clean_terminal);
  int c;

  printf("^Q to quit\r\n");
  while(1){
    c = readKey();
    processKey(c);
  }

  return 0;
}

