#ifndef COPYPASTE_H
#define COPYPASTE_H

char* substr(int startx, int endx, char str[]);
char* copy_text(int startx, int starty, int endx, int endy);
int* mark();
char* cut_text(int marked[], int endx, int endy);
char* paste_text(char * buffer);

#endif