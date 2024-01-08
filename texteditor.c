#include "texteditor.h"

int main(){
    readFile("./test.txt");
}

int err(){
    printf("errno %d\n",errno);
    printf("%s\n",strerror(errno));
    exit(1);
}

//params: filepath is path of the file, current is current node (when passing in pass first node in)
int readFile(char* filepath, struct line * first){
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
        current->next = after;
        current->line_num = counter;
    }


    if (f < 0){
        err();
    }

    char text[LINE_SIZE+1];
    text[LINE_SIZE] = 0;
    int bytes;
    char textchecker[2];
    // while (bytes > 0){ //not necessarily 256 bytes in a line
    //     bytes = read(f, textchecker, 1);
    //     if (bytes <= 0){
    //         endOfFile = 0;
    //     }
    //     if (strcmp(textchecker,"\n") == 0){ //if hit newline   
    //         //goes to new line, refresh memory on structs from music library
    //         current = current->next;
    //     }
    //     else{
    //         strcat(text, textchecker);
    //     }
    // }
    return 0;
}

