.PHONY: compile run clean

run: giga
	./giga
	@[ -f ./data/output.txt ] && cat ./data/output.txt || true

compile giga: giga.o cursor.o setup.o config.o util.o read.o modify.o
	gcc -o giga giga.o cursor.o setup.o config.o util.o read.o modify.o -lncursesw

giga.o: giga.c giga.h cursor.c cursor.h setup.c setup.h util.c util.h read.c read.h modify.c modify.h
	gcc -c giga.c

cursor.o: cursor.c cursor.h giga.c giga.h util.c util.h
	gcc -c cursor.c

setup.o: setup.c setup.h giga.c giga.h config.c config.h
	gcc -c setup.c

config.o: config.c config.h giga.c giga.h util.c util.h
	gcc -c config.c

util.o: util.c util.h
	gcc -c util.c

read.o: read.c read.h giga.c giga.h util.c util.h
	gcc -c read.c

modify.o: modify.c modify.h giga.c giga.h
	gcc -c modify.c


clean:
	rm giga
	rm *.o
