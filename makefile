.PHONY: compile run clean

compile run:
	@echo "cannot compile"

input: input.o util.o
	gcc -o input input.o util.o

input.o: input.c util.h
	gcc -c input.c

util.o: util.c util.h
	gcc -c util.c

clean:
	rm input
	rm *.o
