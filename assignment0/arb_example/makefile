#build the example poly_roots.c from Fredriks examples
all : poly_roots


#-I/home/tobias/local_flint/include -I/home/tobias/local_arb/include
#-L/home/tobias/local_flint/lib -L/home/tobias/local_arb/lib
poly_roots : poly_roots.c
	gcc -o poly_roots -L/home/tobias/local_flint/lib -L/home/tobias/local_arb/lib -I/home/tobias/local_flint/include -I/home/tobias/local_arb/include poly_roots.c -lflint -larb
