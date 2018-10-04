.PHONY : all check clean

TARGETS = newton newton_debug

CFLAGS = -march=native -O3 #seems that -std=c11 takes away nanosleep
HEADS = -I/home/tobias/local_gsl/include
LIBS = -L/home/tobias/local_gsl/lib
lIBS = -lgsl -lgslcblas -lm -lpthread

all : $(TARGETS)

newton : newton.c
	gcc $(CFLAGS) $(HEADS) $(LIBS) -o newton newton.c $(lIBS)

newton_debug:
	gcc -g $(CFLAGS) $(HEADS) $(LIBS) -o newton_debug newton.c $(lIBS)

clean :
	rm -f $(TARGETS)
	rm -f *.ppm
