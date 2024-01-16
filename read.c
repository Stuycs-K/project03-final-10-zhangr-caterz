#include <ncurses.h>
#include "giga.h" // struct line
#include <stdio.h> // fopen, fgets
#include <stdlib.h> // malloc
#include <string.h> // strncpy, strlen
#include "helpbar.h" // helpbar_input, helpbar_alert, infobar_default
#include "util.h" // err, remove_crlf, KEY_CTRL
#include "cursor.h" // init_cursor
#include "read.h"

int readwrite_keyhandler(int ch){
    char to[LINE_SIZE];
    switch(ch){
      case KEY_CTRL('w'):
        helpbar_input("destination: ", to, T.path ? T.path : "");
        save_file(to, T.data);
        helpbar_alert("saved!");
        if(!strlen(T.path)) strncpy(T.path, to, LINE_SIZE+1);
        infobar_default();
        break;
      case KEY_CTRL('r'):
        free_doc(T.data);
        T.data=readFile(T.path, NULL);
        T.curr_line = T.data;
        T.first_line = T.curr_line;
        init_cursor(&T);
        helpbar_alert("reverted!");
        break;
      default:
        return 0;
        break;
    }
    return 1;
} 

struct line* insert_line(struct line* list, char s[], int line_num) {
    struct line* node = malloc(sizeof(struct line));
    node->str = malloc(LINE_SIZE+1);
    strncpy(node->str,s, LINE_SIZE+1);
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
    if(!strlen(filepath)){
        document = insert_line(document, "", 0);
    }
    else{
        int counter = 0;
        char s[LINE_SIZE+1];
        FILE* fp = fopen(filepath,"r");
        if(fp == NULL) err(-1, "error reading file");        

        while(fgets(s, LINE_SIZE, fp) != NULL){
            remove_crlf(s);
            document = insert_line(document, s, counter);
            counter++;
        }
        fclose(fp);
    }
    return document;
}

void save_file(char * filepath, struct line * list){
    struct line* doc = list;
    FILE * fp = fopen(filepath, "w+");
    while (doc != NULL){
        fwrite(doc->str, 1, strlen(doc->str), fp);
        fwrite("\n",1,1,fp);
        doc = doc->next;
    }
    fclose(fp);
}

struct line* free_doc(struct line * list){
    struct line* temp;
    while(list != NULL){
        temp = list->next;
        free(list->str);
        free(list);
        list = temp;
    }
    return NULL;
}

