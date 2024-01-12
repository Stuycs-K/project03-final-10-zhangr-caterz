#include <ncurses.h>
#include "giga.h"
#include <stdlib.h> // malloc
#include <string.h> // strlen
#include "modify.h"

void replace(char* str, int n, char ch){
  char* pos = str+n;
  *pos = ch;
}

void ins_char(char* str, int n, char ch){
  char temp;
  char* pos = str+n;
  while(*pos){
    temp = *pos;
    *pos = ch;
    ch = temp;
    pos++;
  }
  temp = *pos;
  *pos = ch;
  ch = temp; // '\0'
  pos++;
  *pos = '\0';
  E.curr_line->line_len++;
}

void del_char(char* str, int n){
  char* pos = str+n;
  while(*pos){
    *pos = *(pos+1);
    pos++;
  }
  E.curr_line->line_len--;
}

void ins_lf(struct line *node, int n){
  // copy remainding line into str2
  char *pos = node->str+n;
  char str2[LINE_SIZE];
  char *pos2 = str2;
  while(*pos){
    *pos2 = *pos;
    pos++;
    pos2++;
  }
  *pos2 = *pos;
  (node->str)[n] = '\0';

  struct line* node2 = malloc(sizeof(struct line));
  strcpy(node2->str, str2);
  node2->next = node->next;
  node2->previous = node;
  node->next->previous = node2;
  node->next = node2;
  node2->line_num = 0;
  node->line_len = strlen(node->str);
  node2->line_len = strlen(str2);
  refresh_all();
}


void refresh_line(){
  wmove(edit_window, E.cy, 0);
  wclrtoeol(edit_window);
  wprintw(edit_window, "%s", E.curr_line->str);
}

void refresh_all(){
  werase(nums_window);
  werase(edit_window);
  int i=0;
  for(struct line *node = E.data; node; node = node->next) {
    mvwprintw(nums_window, i+E.miny, 0, "%2d", node->line_num);
    mvwprintw(edit_window, i++, 0, "%s", node->str);
  }
  while(i+E.miny<E.maxy){
    mvwprintw(nums_window, i+E.miny, 0, "~");
    i++;
  }
}
