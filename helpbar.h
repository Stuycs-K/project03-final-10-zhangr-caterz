#ifndef HELPBAR_H
#define HELPBAR_H

void helpbar_default();
void infobar_default();
void helpbar_input(char* prompt, char buf[], char* guess);
int helpbar_input_int(char* prompt);
void helpbar_alert(char* str);

#endif
