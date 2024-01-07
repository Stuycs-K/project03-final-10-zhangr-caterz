#ifndef UTIL_H
#define UTIL_H

#define KEY_CTRL(c) ((c) & 0x1f)

int err(int i, char* msg);
int clamp(int x, int min, int max);

#endif
