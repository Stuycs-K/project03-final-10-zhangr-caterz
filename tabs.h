#ifndef TAB_H
#define TAB_H

void create_tab(char *path, int mutable);
void delete_tab(int which);
void switch_tab(int intended);
void tab_keyhandler(int ch);
void show_help();

#endif
