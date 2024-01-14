#ifndef GIGA_H
#define GIGA_H


struct editor_status{
  WINDOW *windows[4];
  int width, height, minx, miny;
  int mode; // 0: insert, 1: replace
  int tabsize;
  int maxlength;
  char *config_path;
  char *help_path;
  struct tab_status *tab;
};

struct tab_status{
  int cx, cy; // cursor desired coordinates
  int cx_real; // actual cursor x-coordinate
  int cy_old; // previous cursor row (used to calculate new current line)
  char *path;
  struct line *data;
  struct line *curr_line;
  struct line *first_line;
};

struct line{
    char *str; //line itself
    struct line* previous;
    struct line* next;
    int line_num; 
    int line_len;
};

extern struct editor_status E;
extern struct tab_status T;
#define LINE_SIZE E.maxlength
#define INFO_WINDOW E.windows[0]
#define HELP_WINDOW E.windows[1]
#define EDIT_WINDOW E.windows[2]
#define NUMS_WINDOW E.windows[3]

#endif
