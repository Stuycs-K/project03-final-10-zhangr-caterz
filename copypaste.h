#ifndef COPYPASTE_H
#define COPYPASTE_H

char* substr(int startx, int endx, char * str, char * buffer);
char* copy_text(int * marked, int endx, int endy, char * buffer);
int* marking(int x, int y);
char* cut_text(int marked[], int endx, int endy);
char* paste_text(char * buffer);

#endif