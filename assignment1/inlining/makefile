CFLAGS=-std=c11 -march=native -O0
TARGETS=mainfile inlined separatefile shouldbeinl separatefile.o

.PHONY : all clean check

all : $(TARGETS)

inlined : inlined.c
	gcc $(CFLAGS) -o inlined inlined.c

mainfile : mainfile.c
	gcc $(CFLAGS) -o mainfile mainfile.c

separatefile: separatefile.c libsep.a
	gcc $(CFLAGS) -o separatefile separatefile.c -I. -L. -lsep

libsep.a : mul_cpx_separatefile.o
	ar -r libsep.a mul_cpx_separatefile.o

mul_cpx_separatefile.o : mul_cpx_separatefile.c mul_cpx_separatefile.h

clean :
	echo "Cleaning up"
	rm -f $(TARGETS)
	rm -f *.o
	rm -f *.a

check :
	./mainfile
	./separatefile
	./inlined
	./shouldbeinl

shouldbeinl : separatefile.c mul_cpx_separatefile.c mul_cpx_separatefile.h
	gcc $(CFLAGS) -o shouldbeinl separatefile.c mul_cpx_separatefile.c mul_cpx_separatefile.h

separatefile.o : separatefile.c

#Henrik's simpler solution. This also makes sure that nothing is inlined
#mul_cpx_separatefile.o : mul_cpx_separatefile.c mul_cpx_separatefile.h
#separatefile : separatefile.c mul_cpx_separatefile.o
#	gcc $(CFLAGS) -o separatefile separatefile.c mul_cpx_separatefile.o
