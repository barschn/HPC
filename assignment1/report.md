<script type="text/javascript" async
  src="https://cdn.mathjax.org/mathjax/latest/MathJax.js?config=TeX-MML-AM_CHTML">
</script>

# Assignment report 1

What follows is a report of Tobias Magnusson and Henrik Imbergs solution of assignment 1.

## Time

In this part we implement a program consisting of nested loops. In the inner loop, we compute the sum of the first billion integers, and in the outer loop we write the sum to `stdout` and time every iteration. We also, for good measure, time the total and average execution time.

~~~C
void main(int argc, char *argv[]){
        struct timespec start,stop,absstart,absstop;
        long S=0;
        int reps=strtol(argv[1],NULL,10);
        long double elapsed;
        timespec_get(&absstart, TIME_UTC);
        for(size_t n=0; n<reps; ++n){
                timespec_get(&start, TIME_UTC);
                for(size_t i=0; i<SIZE; ++i)
                        S+=i;
                timespec_get(&stop, TIME_UTC);
                printf("Result: %ld\n",S);
                elapsed=(stop.tv_sec+1.0e-9*stop.tv_nsec)-(start.tv_sec+1.0e-9*start.tv_nsec);
                printf("Took %.15Lf secs\n",elapsed);
                S=0;
        }
        timespec_get(&absstop, TIME_UTC);
        elapsed=(absstop.tv_sec+1.0e-9*absstop.tv_nsec)-(absstart.tv_sec+1.0e-9*absstart.tv_nsec);
        printf("Total time %.15Lf secs\n",elapsed);
        printf("Average time %.15Lf secs\n",elapsed/reps);
        exit(0); //Need to return stuff, if you don't return 0 make will assume error
        //Returning 1 will make (or bash) not run stuff afterwards
}
~~~

We compile this program with all possible optimization levels and generate assembler code. See the `makefile` below.

~~~make
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
~~~

Running `make check` we may get something along the lines of what follows below.

~~~
./bigsum_opt0 3
Result: 499999999500000000
Took 1.713405370712280 secs
Result: 499999999500000000
Took 1.703644275665283 secs
Result: 499999999500000000
Took 1.702723503112793 secs
Total time 5.119848489761353 secs
Average time 1.706616163253784 secs
./bigsum_opt1 3
Result: 499999999500000000
Took 0.300299644470215 secs
Result: 499999999500000000
Took 0.287335634231567 secs
Result: 499999999500000000
Took 0.287215232849121 secs
Total time 0.874917984008789 secs
Average time 0.291639328002930 secs
./bigsum_opt2 3
Result: 499999999500000000
Took 0.000000000000000 secs
Result: 499999999500000000
Took 0.000000238418579 secs
Result: 499999999500000000
Took 0.000000000000000 secs
Total time 0.000106811523438 secs
Average time 0.000035603841146 secs
./bigsum_opt3 3
Result: 499999999500000000
Took 0.000000000000000 secs
Result: 499999999500000000
Took 0.000000000000000 secs
Result: 499999999500000000
Took 0.000000000000000 secs
Total time 0.000063896179199 secs
Average time 0.000021298726400 secs
./bigsum_opts 3
Result: 499999999500000000
Took 0.000000238418579 secs
Result: 499999999500000000
Took 0.000000000000000 secs
Result: 499999999500000000
Took 0.000000000000000 secs
Total time 0.000174522399902 secs
Average time 0.000058174133301 secs
./bigsum_optg 3
Result: 499999999500000000
Took 0.580969810485840 secs
Result: 499999999500000000
Took 0.574371814727783 secs
Result: 499999999500000000
Took 0.574378967285156 secs
Total time 1.729788541793823 secs
Average time 0.576596180597941 secs
~~~

We see that on average `-O3` is fastest. Note also that `timespec` doesn't time the individual loop times correctly on optimization levels `-O2`, `-O3`, and `-Os`. Ordering the optimization levels by average execution time (of the program) we get

1. `-O3` with 0.000021298726400 seconds
2. `-O2` with 0.000035603841146 seconds
3. `-Os` with 0.000058174133301 seconds
4. `-O1` with 0.291639328002930 seconds
5. `-Og` with 0.576596180597941 seconds
6. `-O0` with 1.706616163253784 seconds

Let's compare this result with the assembler code. We first list the sizes (in bytes).

~~~bash
[tobias@gantenbein time]$ ls -lS *.s
-rw-rw-r--. 1 tobias tobias 2646 20 sep 18.27 bigsum_opt2.s
-rw-rw-r--. 1 tobias tobias 2646 20 sep 18.27 bigsum_opt3.s
-rw-rw-r--. 1 tobias tobias 2630 20 sep 18.27 bigsum_opt0.s
-rw-rw-r--. 1 tobias tobias 2537 20 sep 18.27 bigsum_optg.s
-rw-rw-r--. 1 tobias tobias 2491 20 sep 18.27 bigsum_opt1.s
-rw-rw-r--. 1 tobias tobias 2362 20 sep 18.27 bigsum_opts.s
~~~

This corresponds well with what is written in the `gcc` [documentation](https://gcc.gnu.org/onlinedocs/gcc-8.2.0/gcc/Optimize-Options.html#Optimize-Options). For example `-Os` optimizes for code size, and indeed `bigsum_opts.s` is smallest.

Let's delve a bit deeper into the actual timing, by comparing the actual assembler code of the slowest -- `-O0`, with the fastest -- `-O3`.


## Inlining

## Locality

## Indirect addressing

## Writing to HDD and to SSD

## Valgrind

## Profiling
