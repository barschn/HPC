#Don't forget to run export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/tobias/local_gsl/lib
#I don't how this behaves together with tmux

.PHONY : all check clean

CFLAGS = -std=c11 -march=native -O3

all : example_gsl

example_gsl : example_gsl.c
	gcc $(CFLAGS) -I/home/tobias/local_gsl/include -o example_gsl -L/home/tobias/local_gsl/lib example_gsl.c -lgsl -lgslcblas -lm
