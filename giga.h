#ifndef GIGA_H
#define GIGA_H

#define LINE_SIZE 256

struct editor_status{
  int maxx, maxy, minx, miny;
  int cx, cy; // cursor desired coordinates
  int cx_real; // actual cursor x-coordinate
  int cy_old; // previous cursor row (used to calculate new current line)
  char* path;
  struct line* curr_line;
};

struct line{
    char str[LINE_SIZE+1]; //line itself
    struct line* previous;
    struct line* next;
    int line_num; 
    int line_len;
};

extern struct editor_status E;
extern WINDOW *info_window;
extern WINDOW *help_window;
extern WINDOW *edit_window;
extern WINDOW *nums_window;
extern struct line *data;

#endif
