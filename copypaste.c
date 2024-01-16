#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h> 
#include "util.h"
#include "giga.h"
#include "modify.h"
#include "copypaste.h"

char* substr(int startx, int endx, char str[]){ 
	char subs[LINE_SIZE];
	for (int i = startx; i <= endx; i++){
		strcat(subs, str[i]);
	}
	return subs;
}

//for marking (ctrl-z)
int * mark(int x, int y){
	int markx = x;
	int marky = y;
	int* coords = malloc(sizeof(int) * 2);
	coords[0] = markx;
	coords[1] = marky;
	return coords;
}

//only works for same line (limitation- can only have a length of LINE_SIZE at a time)
//marked = marked cursor coordinates, endx & endy end cursor coordinates when (ctrl-c) is hit
char* copy_text(int * marked, int endx, int endy){
	char buffer[LINE_SIZE];
	int startx = marked[0];
	int starty = marked[1];
	if (startx < endx){
		strcpy(buffer, substr(startx, endx, E.data->str));
	}
	else{
		strcpy(buffer, substr(endx, startx, E.data->str));
	}

}

//pasting test written to buffer
char* paste_text(char * buffer){
	int index = 0;
	while(buffer[index] != NULL){
		ins_char(T.curr_line->str,T.cx_real,buffer[index]);
		moveCursor(buffer[index]);
		index++;
	}
	return buffer;
}

char* cut_text(int * marked, int endx, int endy){
	
}
