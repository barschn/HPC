#Don't forget to run export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/tobias/local_gsl/lib
#I don't how this behaves together with tmux

.PHONY : all check clean

CFLAGS = -std=c11 -march=native -O3
HEADS = -I/home/tobias/local_gsl/include
LIBS = -L/home/tobias/local_gsl/lib
lIBS = -lgsl -lgslcblas -lm

all : example_gsl complex_in_gsl newton_gsl

example_gsl : example_gsl.c
	gcc $(CFLAGS) $(HEADS) $(LIBS) -o example_gsl example_gsl.c $(lIBS)

complex_in_gsl : complex_in_gsl.c
	gcc $(CFLAGS) $(HEADS) $(LIBS) -o complex_in_gsl complex_in_gsl.c $(lIBS)

newton_gsl : newton_gsl.c
	gcc $(CFLAGS) $(HEADS) $(LIBS) -o newton_gsl newton_gsl.c $(lIBS) -lpthread
