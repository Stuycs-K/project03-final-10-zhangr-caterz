#include <ncurses.h>
#include "giga.h" // struct line
#include <stdio.h> // fopen, fgets
#include <stdlib.h> // malloc
#include <string.h> // strcpy, strlen
#include "util.h" // err, remove_crlf
#include "read.h"

struct line* insert_line(struct line* list, char s[], int line_num) {
    struct line* node = malloc(sizeof(struct line));
    strcpy(node->str,s);
    node->next = NULL;
    node->line_num = line_num;
    node->previous = NULL;
    node->line_len = strlen(s);
    if (list == NULL){ //first line
        list = node;
        return list;
    }

    struct line * current = list;

    while(current->next != NULL){
        current = current->next;
    }

    if(current->line_num == line_num - 1){
        node->previous = current;
    }
    

    if (current->next == NULL){
        current->next = node;
        return list;
    }
    return list;
}

//params: filepath is path of the file, current is current node (when passing in pass first node in)
struct line * readFile(char* filepath, struct line * document){
    int counter = 0;
    char s[LINE_SIZE+1];
    FILE* fp = fopen(filepath,"r");
    if(fp == NULL) {
        err(-1, "error reading file");        
    }


    while(fgets(s, 256, fp) != NULL){
        remove_crlf(s);
        document = insert_line(document, s, counter);
        counter++;
    }
    fclose(fp);
    return document;
}

void save_file(char * filepath, struct line * list){
    struct line* doc = list;
    FILE * fp = fopen(filepath, "w+");
    char* counter = malloc(LINE_SIZE); //format [#]
    int count;
    char countbuffer[20];
    while (list != NULL){
        sprintf(countbuffer, "%d", count);
        strcat(counter, "[");
        strcat(counter, countbuffer);
        strcat(counter, "]");
        count++;
        fwrite(doc->str, 1, sizeof(doc->str), fp);
        fwrite("\n", 1, 1, fp);
        list = list->next;
    }
}