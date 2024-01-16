#ifndef READ_H
#define READ_H

int readwrite_keyhandler(int ch);

struct line* readFile(char* filepath, struct line * document);
void save_file(char * filepath, struct line* list);
struct line* free_doc(struct line * list);

#endif
