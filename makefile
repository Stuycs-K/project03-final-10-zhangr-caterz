.PHONY: compile run clean

compile run:
	@echo "cannot compile"

texteditor: texteditor.o
	gcc -o texteditor texteditor.o

texteditor.o: texteditor.c texteditor.h
	gcc -c texteditor.c

clean:
	rm input
	rm *.o
