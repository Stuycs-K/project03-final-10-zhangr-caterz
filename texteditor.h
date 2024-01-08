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

struct line{
    char str[LINE_SIZE+1]; //line itself
    struct line* previous;
    struct line* next;
    int line_num; 
};
int err();
struct line* readFile(char* filepath, struct line * document);
struct line* insert_line(struct line* list, char s[], int line_num);
void print_list(struct line* list);


