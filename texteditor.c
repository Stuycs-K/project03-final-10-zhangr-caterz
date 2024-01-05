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
int readFile(char* filepath){
    int f = open(filepath,O_RDONLY,0);
    if (f < 0){
        err();
    }
    char text[LINE_SIZE+1];
    text[LINE_SIZE] = 0;
    int bytes;
    while (bytes = read(f, text, LINE_SIZE)){ //not necessarily 256 bytes in a line
        if (text < 0){
            err();
        }
        printf("%s",text);
    }
    return 0;
}