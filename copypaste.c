#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h> 
#include "util.h"
#include "giga.h"
#include "modify.h"
#include "copypaste.h"

char* substr(int startx, int endx, char * str, char * buffer){ 
	strncpy(buffer, str+startx, endx-startx);
	return buffer;
}

//for marking (ctrl-z)
int * marking(int x, int y){
	int markx = x;
	int marky = y;
	int* coords = malloc(sizeof(int) * 2);
	coords[0] = markx;
	coords[1] = marky;
	return coords;
}

//only works for same line (limitation- can only have a length of LINE_SIZE at a time)
//marked = marked cursor coordinates, endx & endy end cursor coordinates when (ctrl-c) is hit
char* copy_text(int * marked, int endx, int endy, char * buffer){
	int startx = marked[0];
	int starty = marked[1];
	if (startx < endx){
		strcpy(buffer, substr(startx, endx, T.data->str, buffer));
	}
	else{
		strcpy(buffer, substr(endx, startx, T.data->str, buffer));
	}
	return buffer;
}

//pasting test written to buffer
char* paste_text(char * buffer){
	int index = 0;
	while(buffer[index] == '\0' != 0){
		ins_char(T.curr_line->str,T.cx_real,buffer[index]);
		T.cx+=1;
		index++;
	}
	return buffer;
}

char* cut_text(int * marked, int endx, int endy){
	
}
