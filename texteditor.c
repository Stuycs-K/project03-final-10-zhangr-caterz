#include "texteditor.h"

int main(){
    struct line * document = NULL;
    document = readFile("./test.txt", document);
    print_list(document);
    return 0;
}

int err(){
    printf("errno %d\n",errno);
    printf("%s\n",strerror(errno));
    exit(1);
}

//params: filepath is path of the file, current is current node (when passing in pass first node in)
struct line * readFile(char* filepath, struct line * document){
    int counter = 1;
    char s[LINE_SIZE+1];
    FILE* fp = fopen(filepath,"r");
    if(fp == NULL) {
        err();        
    }

    while(fgets(s, 256, fp) != NULL){
        document = insert_line(document, s, counter);
        counter++;
    }

    return document;
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
        printf("tworks!");
        current->next = node;
        return list;
    }
    return list;
}

void print_list(struct line* list) {
    int i = 0;
    while(list != NULL) {
        printf("[%d]", list->line_num);
        printf("%s\n", list->str);
        list = list->next;
        i++;
    }
}
