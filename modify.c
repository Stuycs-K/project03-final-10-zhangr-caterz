#include <ncurses.h>
#include "giga.h"
#include <stdlib.h> // malloc
#include <string.h> // strlen
#include "visual.h" // refresh_line, refresh_all
#include "modify.h"

void replace(char* str, int n, char ch){
  char* pos = str+n;
  if(!*pos){
    *(pos+1) = '\0';
    E.curr_line->line_len++;
  }
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

void update_line_nums(struct line *node, int n){
  while(node){
    node->line_num = n;
    node = node->next;
    n++;
  }
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

  // update linked list
  struct line* node2 = malloc(sizeof(struct line));
  strcpy(node2->str, str2);
  node2->next = node->next;
  node2->previous = node;
  if(node->next) node->next->previous = node2;
  node->next = node2;
  update_line_nums(node2, node->line_num+1);
  node->line_len = strlen(node->str);
  node2->line_len = strlen(str2);
}

// node is the node BEFORE the line feed
void del_lf(struct line *node){
  struct line *node2 = node->next;
  char *pos = node->str + node->line_len;
  char *pos2 = node2->str;
  while(*pos2){
    *pos = *pos2;
    pos++;
    pos2++;
  }
  *pos = *pos2;

  node->next = node2->next;
  if(node2->next) node2->next->previous = node;
  update_line_nums(node, node->line_num);
  node->line_len = strlen(node->str);
  free(node2);
}

