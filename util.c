#include "util.h"

int err(int i, char* msg){
  if(i<0){
    printf("Error: %s - %s\n", msg, strerror(errno));
    exit(1);
  }
  return i;
}

int clamp(int x, int min, int max){
  if(x < min) return min;
  if(x > max) return max;
  return x;
}
