.PHONY : all check clean

TARGETS = newton_draft1

CFLAGS = -std=c11 -march=native -O3
HEADS = -I/home/tobias/local_gsl/include
LIBS = -L/home/tobias/local_gsl/lib
lIBS = -lgsl -lgslcblas -lm -lpthread

all : $(TARGETS)

newton_draft1 : newton_draft1.c
	gcc $(CFLAGS) $(HEADS) $(LIBS) -o newton_draft1 newton_draft1.c $(lIBS)
clean :
	rm -f $(TARGETS)
