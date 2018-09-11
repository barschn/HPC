#build the example poly_roots.c from Fredriks examples
all : heap

heap : heap.o
	gcc -o heap heap.o

heap.o : heap.c
	gcc -O1 -c heap.c
