.PHONY: compile run clean

run: giga
	./giga
	@[ -f ./data/output.txt ] && cat ./data/output.txt || true

compile giga: giga.o cursor.o setup.o config.o util.o read.o modify.o helpbar.o
	gcc -Wall -Werror -o giga giga.o cursor.o setup.o config.o util.o read.o modify.o helpbar.o -lncursesw

giga.o: giga.c giga.h cursor.c cursor.h setup.c setup.h util.c util.h read.c read.h modify.c modify.h helpbar.c helpbar.h
	gcc -c giga.c

cursor.o: cursor.c cursor.h giga.c giga.h util.c util.h
	gcc -c cursor.c

setup.o: setup.c setup.h giga.c giga.h config.c config.h modify.c modify.h cursor.c cursor.h helpbar.c helpbar.h
	gcc -c setup.c

config.o: config.c config.h giga.c giga.h util.c util.h
	gcc -c config.c

util.o: util.c util.h
	gcc -c util.c

read.o: read.c read.h giga.c giga.h util.c util.h
	gcc -c read.c

modify.o: modify.c modify.h giga.c giga.h
	gcc -c modify.c

helpbar.o: helpbar.c helpbar.h giga.c giga.h
	gcc -c helpbar.c


clean:
	rm giga
	rm *.o
