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
  buffer[endx-startx+1] = '\0';
	return buffer;
}

//for marking (ctrl-z)
int * marking(int x, int y){
	int markx = x;
	int marky = y;
	int* coords = malloc(sizeof(int) * 2);
	coords[0] = markx;
	coords[1] = marky;
	// printf("%d , %d", coords[0], coords[1]);
	return coords;
}

//only works for same line (limitation- can only have a length of LINE_SIZE at a time)
//marked = marked cursor coordinates, endx & endy end cursor coordinates when (ctrl-c) is hit
char* copy_text(int * marked, int endx, int endy, char * buffer){
	int startx = marked[0];
	int starty = marked[1];
	if (startx < endx){
		substr(startx, endx, T.curr_line->str, buffer);
	}
	else{
		substr(endx, startx, T.curr_line->str, buffer);
	}
	return buffer;
}

//pasting test written to buffer
char* paste_text(char * buffer){
	int index = 0;
	while(buffer[index] != '\0'){
		ins_char(T.curr_line->str,T.cx_real,buffer[index]);
		T.cx+=1;
		T.cx_real+=1;
		index++;
	}
	return buffer;
}
