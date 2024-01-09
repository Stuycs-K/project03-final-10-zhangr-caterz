#ifndef READ_H
#define READ_H

struct line* readFile(char* filepath, struct line * document);
void save_file(char * filepath, struct line* list);
#endif
