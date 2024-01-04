#include "texteditor.h"

int main(){

}

int err(){
    printf("errno %d\n",errno);
    printf("%s\n",strerror(errno));
    exit(1);
}

//params: filepath is path of the file, text is the char array to the whole file.
int readFile(char* filepath, char* text){
    int f = open(filepath,O_RDONLY,0);
    if (f < 0){
        err();
    }
}