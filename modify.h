#ifndef MODIFY_H
#define MODIFY_H

void modify_keyhandler(int ch);

void replace(char *str, int n, char ch);
void ins_char(char *str, int n, char ch);
void del_char(char *str, int n);

void ins_lf(struct line *node, int n);
void del_lf(struct line *node);

#endif
