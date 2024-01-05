#include "util.h"

int err(int i, char* msg){
  if(i<0){
    printf("Error: %s - %s\n", msg, strerror(errno));
    exit(1);
  }
  return i;
}
