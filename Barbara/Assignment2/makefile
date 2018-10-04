CC = gcc
CFLAGS = -O3 -march=native -pthread
LIBRARIES = -lm 

.PHONY : newton

newton :
	$(CC) -o $@ $(CFLAGS) newton.c $(LIBRARIES)

clean : 
	rm -f newton newton_attractors_xd.ppm newton_convergence_xd.ppm

