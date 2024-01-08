#include "texteditor.h"

int main(){
    struct line * first = malloc(sizeof(struct line));
    readFile("./test.txt", first);

}

int err(){
    printf("errno %d\n",errno);
    printf("%s\n",strerror(errno));
    exit(1);
}

//params: filepath is path of the file, current is current node (when passing in pass first node in)
int readFile(char* filepath, struct line * first){
    struct line * previous = malloc(sizeof(struct line));
    struct line * current = malloc(sizeof(struct line));
    struct line * after = malloc(sizeof(struct line));
    int counter = 1;
    char *s;
    FILE* fp = fopen(filepath,"r");
    if(fp == NULL) {
        err();        
    }
    while(fgets(str, 256, fp) != NULL){
        strcpy(current->str, s);
        if (counter != 1){
            current->previous = NULL;
        }
        current->next = after;
        current->line_num = counter;
        counter++;
        previous = current;
        current = after;
        after = malloc(sizeof(struct line));
    }
}



