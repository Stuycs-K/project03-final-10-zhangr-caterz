.PHONY: compile run clean
run: giga
	./giga

compile giga: giga.o cursor.o setup.o util.o
	gcc -o giga giga.o cursor.o setup.o util.o -lncurses

giga.o: giga.c giga.h cursor.h setup.h util.h
	gcc -c giga.c

cursor.o: cursor.c cursor.h giga.h util.c
	gcc -c cursor.c

setup.o: setup.c setup.h giga.h
	gcc -c setup.c

util.o: util.c util.h
	gcc -c util.c

texteditor: texteditor.o
	gcc -o texteditor texteditor.o

texteditor.o: texteditor.c texteditor.h
	gcc -c texteditor.c

clean:
	rm giga
	rm texteditor


