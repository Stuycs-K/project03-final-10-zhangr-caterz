#ifndef UTIL_H
#define UTIL_H

#define MIN(X,Y) ((X) < (Y) ? (X) : (Y))
#define MAX(X,Y) ((X) > (Y) ? (X) : (Y))

#define KEY_CTRL(c) ((c) & 0x1f)

int err(int i, char* msg);
int clamp(int x, int min, int max);
void split(char* str, char** args);
void remove_crlf(char *str);

#endif
