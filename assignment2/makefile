.PHONY : all check clean

TARGETS = newton

all : $(TARGETS)

newton : newton.c
	gcc -O3 -march=native -std=c11 newton.c -o newton -lpthread

clean :
	rm -f $(TARGETS)
