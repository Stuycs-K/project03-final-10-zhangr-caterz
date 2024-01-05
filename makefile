.PHONY: compile run clean

compile run:
	@echo "cannot compile"

input: input.o
	gcc -o input input.o

input.o: input.c
	gcc -c input.c

clean:
	rm input
	rm *.o
