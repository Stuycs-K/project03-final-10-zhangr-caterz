#include "texteditor.h"

void removeCR(char *str){
  int i=0;
  while(str[i]){
    if(str[i]=='\r' || str[i]=='\n') str[i] = '\0';
    i++;
  }
}

struct line* insert_line(struct line* list, char s[], int line_num) {
    struct line* node = malloc(sizeof(struct line));
    strcpy(node->str,s);
    node->next = NULL;
    node->line_num = line_num;
    node->previous = NULL;
    if (list == NULL){ //first line
        list = node;
        return list;
    }

    struct line * current = list;

    while(current->next != NULL){
        current = current->next;
        if(current->line_num == line_num - 1){
            node->previous = current;
        }
    }

    if (current->next == NULL){
        current->next = node;
        return list;
    }
    return list;
}

//params: filepath is path of the file, current is current node (when passing in pass first node in)
struct line * readFile(char* filepath, struct line * document){
    int counter = 1;
    char s[LINE_SIZE+1];
    FILE* fp = fopen(filepath,"r");
    if(fp == NULL) {
        err(-1, "error reading file");        
    }

    while(fgets(s, 256, fp) != NULL){
        removeCR(s);
        document = insert_line(document, s, counter);
        counter++;
    }
    fclose(fp);
    return document;
}
