all: sig.c
	gcc sig.c -o sig

clean:
	rm sig
	rm *~

run: sig
	./sig