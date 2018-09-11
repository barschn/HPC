.PHONY : all

ARG=3

all : opt0 opt1 opt2 opt3 opts optg

opt0 : bigsum.c
	gcc -S -O0 bigsum.c -o bigsum_opt0.s
	gcc -O0 bigsum.c -o bigsum_opt0

opt1 : bigsum.c
	gcc -S -O1 bigsum.c -o bigsum_opt1.s
	gcc -O1 bigsum.c -o bigsum_opt1

opt2 : bigsum.c
	gcc -S -O2 bigsum.c -o bigsum_opt2.s
	gcc -O2 bigsum.c -o bigsum_opt2

opt3 : bigsum.c
	gcc -S -O3 bigsum.c -o bigsum_opt3.s
	gcc -O3 bigsum.c -o bigsum_opt3

opts : bigsum.c
	gcc -S -Os bigsum.c -o bigsum_opts.s
	gcc -Os bigsum.c -o bigsum_opts

optg : bigsum.c
	gcc -S -Og bigsum.c -o bigsum_optg.s
	gcc -Og bigsum.c -o bigsum_optg

clean :
	rm -f bigsum_*

check :
	./bigsum_opt0 $(ARG)
	./bigsum_opt1 $(ARG)
	./bigsum_opt2 $(ARG)
	./bigsum_opt3 $(ARG)
	./bigsum_opts $(ARG)
	./bigsum_optg $(ARG)
