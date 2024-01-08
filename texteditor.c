#include "texteditor.h"

int main(){
    struct line * document = NULL;
    readFile("./test.txt", document);

    return 0;
}

int err(){
    printf("errno %d\n",errno);
    printf("%s\n",strerror(errno));
    exit(1);
}

//params: filepath is path of the file, current is current node (when passing in pass first node in)
int readFile(char* filepath, struct line * document){
    // struct line * previous = malloc(sizeof(struct line));
    // struct line * current = malloc(sizeof(struct line));
    // struct line * after = malloc(sizeof(struct line));
    // current = first;
    int counter = 1;
    char s[LINE_SIZE+1];
    FILE* fp = fopen(filepath,"r");
    if(fp == NULL) {
        err();        
    }
    
    while(fgets(s, 256, fp) != NULL){
        insert_line(document, s, counter);
        counter++;
        // if (counter != 1){
        //     current->previous = NULL;
        // }
        // current->next = after;
        // current->line_num = counter;
        // counter++;
        // previous = current;
        // current = after;
        // after = malloc(sizeof(struct line));
    }
    return 0;
}

struct line* insert_line(struct line* list, char s[], int line_num) {
    struct line* node = malloc(sizeof(struct line));
    strcpy(node->str,s);
    node->next = NULL;
    node->line_num = line_num;
    node->previous = NULL;
    strcpy(node->str, s);
    if (list == NULL){
        list = node;
        return list;
    }
    struct line * current = list;
    struct line * previous;
    for (int i = 1; i <= line_num; i++){
        if (i = line_num - 1){
            node->previous = current;
        }
        current = current->next;
    }
    if (current->next == NULL){
        current->next = node;
        return list;
    }
    node->next = current->next;
    current->next = node;
    return list;
}


