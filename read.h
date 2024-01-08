#ifndef READ_H
#define READ_H
#define LINE_SIZE 256

struct line{
    char str[LINE_SIZE+1]; //line itself
    struct line* previous;
    struct line* next;
    int line_num; 
};
struct line* readFile(char* filepath, struct line * document);

#endif
