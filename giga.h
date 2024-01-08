#ifndef GIGA_H
#define GIGA_H

struct editor_status{
  int maxx, maxy, minx, miny;
  int cx, cy;
  char* path;
};

extern struct editor_status E;
extern WINDOW *info_window;
extern WINDOW *help_window;
extern WINDOW *edit_window;
extern WINDOW *nums_window;
extern struct line *data;

#endif
