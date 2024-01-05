#include "texteditor.h"
#define LINE_SIZE 256

int main(){
    readFile("./test.txt");
}

int err(){
    printf("errno %d\n",errno);
    printf("%s\n",strerror(errno));
    exit(1);
}

//params: filepath is path of the file
int readFile(char* filepath, struct lines){
    int f = open(filepath,O_RDONLY,0);
    if (f < 0){
        err();
    }
    char text[LINE_SIZE+1];
    text[LINE_SIZE] = 0;
    int bytes;
    int endOfFile = 1; //0 indicates end of file;
    char textchecker[2];
    while (endOfFile){ //not necessarily 256 bytes in a line
        bytes = read(f, textchecker, 1);
        if (bytes <= 0){
            endOfFile = 0;
        }
        if (strcmp(textchecker,"\n") == 0){ //if hit newline
            //goes to new line, refresh memory on structs from music library
        }
        else{
            strcat(text, textchecker);
        }
    }
    return 0;
}

