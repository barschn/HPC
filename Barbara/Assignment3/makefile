CC = gcc
CFLAGS = -O3 -march=native -fopenmp
LIBRARIES = -lm 

.PHONY : cell_distance

cell_distance :
	$(CC) -o $@ $(CFLAGS) cell_distance.c $(LIBRARIES)

clean : 
	rm -f cell_distance
