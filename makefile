.PHONY: compile run clean

compile run:
	@echo "cannot compile"

giga: giga.o input.o setup.o util.o
	gcc -o giga giga.o input.o setup.o util.o -lncurses

#input: input.o setup.o util.o
#	gcc -o input input.o setup.o util.o -lncurses

giga.o: giga.c giga.h input.h setup.h util.h
	gcc -c giga.c

input.o: input.c giga.h input.h setup.h util.h
	gcc -c input.c

setup.o: setup.c giga.h input.h setup.h util.h
	gcc -c setup.c

util.o: util.c util.h
	gcc -c util.c

clean:
	rm input
	rm *.o
