#include <stdio.h> // printf, fgetc
#include <unistd.h> // stdin_fileno
#include <termios.h> // terminal functions
#include <errno.h> // errno
#include <string.h> // strerror
#include <stdlib.h> // exit

// original termios settings
struct termios orig_termios;

int err(int i, char* msg);


// Set terminal to raw mode
int setup_terminal(){
  tcgetattr(STDIN_FILENO, &orig_termios); 

  struct termios term;
  err(tcgetattr(STDIN_FILENO, &term), "tcgetattr");
  cfmakeraw(&term);
  err(tcsetattr(STDIN_FILENO, TCSAFLUSH, &term), "tcsetattr");

  return 0;
}

// Revert terminal to the original interface
int clean_terminal(){
  err(tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios), "tcsetattr");
  return 0;
}


int main(){
  setup_terminal();
  char c;

  while(err(read(STDIN_FILENO, &c, 1), "read") && c!='q'){
    printf("%d: %c\r\n", c, c);
  }

  clean_terminal();
  return 0;
}

int err(int i, char* msg){
  if(i<0){
    printf("Error: %s - %s\n", msg, strerror(errno));
    clean_terminal();
    exit(1);
  }
  return i;
}
