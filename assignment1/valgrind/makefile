.PHONY : val clean all

all : valgO2 valgO0

valgO2 : valg.c
	gcc -O2 -std=c11 -march=native -o valgO2 valg.c
valgO0 : valg.c
	gcc -O0 -std=c11 -march=native -o valgO0 valg.c

val :
	valgrind --tool=memcheck --leak-check=yes ./valgO0
	valgrind --tool=memcheck --leak-check=yes ./valgO2

clean :
	rm -f valgO*
