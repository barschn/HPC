.PHONY: all check clean cleanbin

CFLAGS=-std=c11 -march=native
CO0=$(CFLAGS) -O0
CO2=$(CFLAGS) -O2

all : writeints
	gcc $(CO2) -o writeints writeints.c

clean :
	rm -f writeints
	rm -f *.bin
	rm -f /run/mount/scratch/tobias/ints.bin
cleanbin :
	rm -f *.bin
	rm -f /run/mount/scratch/tobias/ints.bin

check :
	./writeints
