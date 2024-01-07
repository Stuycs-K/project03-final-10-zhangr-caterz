#ifndef GIGA_H
#define GIGA_H


struct editor_status{
  int maxx, maxy, minx, miny;
  int cx, cy;
};


extern struct editor_status E;
extern WINDOW *info_window;
extern WINDOW *help_window;
extern WINDOW *edit_window;

#endif
