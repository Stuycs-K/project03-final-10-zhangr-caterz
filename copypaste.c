#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h> 
#include "util.h"
#include "modify.h"

char* substr(int startx, int endx, char str[]){ 
	char subs[LINE_SIZE];
	for (int i = startx; i < endx; i++){
		strcat(subs, str[i]);
	}
	return subs;
}

//hit ctrl-z, use arrow keys
//only works for same line (limitation- can only have a length of LINE_SIZE at a time)
char* copy_text(int startx, int starty, int endx, int endy){
	char buffer[LINE_SIZE];
	strcpy(buffer, substr(startx, endx, E.data->str));

}

int[] markplace(int cx_real, int cy){
	
}
