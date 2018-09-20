CFLAGS=-std=c11 -march=native -pg
TARGETS=locality locality_fast

.PHONY : all check

all : $(TARGETS)

locality : locality.c
	gcc $(CFLAGS) -O0 -o locality0 locality.c
	gcc $(CFLAGS) -O2 -o locality2 locality.c

locality_fast : locality_fast.c	
	gcc $(CFLAGS) -O0 -o locality_fast0 locality_fast.c
	gcc $(CFLAGS) -O0 -ftest-coverage -fprofile-arcs -o locality_fast0_cov locality_fast.c
	gcc $(CFLAGS) -O2 -o locality_fast2 locality_fast.c

check :
	echo "Slow, -O0"
	./locality0
	echo "Slow, -O2"
	./locality2
	echo "Fast, -O0"
	./locality_fast0
	echo "Fast, -O2"
	./locality_fast2
