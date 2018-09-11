#build the example poly_roots.c from Fredriks examples
all : stack

stack : stack.o
	gcc -o stack stack.o

stack.o : stack.c
	gcc -O1 -c stack.c
