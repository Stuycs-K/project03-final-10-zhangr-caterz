.PHONY: compile run clean
run: giga
	./giga

compile giga: giga.o cursor.o setup.o config.o util.o
	gcc -o giga giga.o cursor.o setup.o config.o util.o -lncurses

giga.o: giga.c giga.h cursor.c cursor.h setup.c setup.h util.c util.h
	gcc -c giga.c

cursor.o: cursor.c cursor.h giga.c giga.h util.c util.h
	gcc -c cursor.c

setup.o: setup.c setup.h giga.c giga.h config.c config.h
	gcc -c setup.c

config.o: config.c config.h giga.c giga.h util.c util.h
	gcc -c config.c

util.o: util.c util.h
	gcc -c util.c

texteditor: texteditor.o
	gcc -o texteditor texteditor.o

texteditor.o: texteditor.c texteditor.h
	gcc -c texteditor.c

clean:
	rm giga
	rm texteditor


