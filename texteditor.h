#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/socket.h> 
#include <netdb.h>

#define LINE_SIZE 256
int err();
int readFile(char* filepath);
struct line{
    char str[LINE_SIZE+1]; //line itself
    struct line* previous;
    struct line* next;
    int line_num; 
};