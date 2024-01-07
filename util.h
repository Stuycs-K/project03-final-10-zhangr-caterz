#include <stdio.h> // printf
#include <stdlib.h> // exit
#include <errno.h> // errno
#include <string.h> // strerror

#ifndef UTIL_H
#define UTIL_H
int err(int i, char* msg);
int clamp(int x, int min, int max);
#endif
