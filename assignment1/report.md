<script type="text/javascript" async
  src="https://cdn.mathjax.org/mathjax/latest/MathJax.js?config=TeX-MML-AM_CHTML">
</script>

# Assignment report 1

What follows is a report of Tobias Magnusson and Henrik Imbergs solution of assignment 1.

## Time

In this part we implemented a program consisting of nested loops. In the inner loop, we computed the sum of the first billion integers, and in the outer loop we wrote the sum to `stdout` and timed every iteration. We also, for good measure, timed the total and average execution time.

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
                printf("Took %Lf10 secs\n",elapsed);
                S=0;
        }
        timespec_get(&absstop, TIME_UTC);
        elapsed=(absstop.tv_sec+1.0e-9*absstop.tv_nsec)-(absstart.tv_sec+1.0e-9*absstart.tv_nsec);
        printf("Total time %Lf10 secs\n",elapsed);
        printf("Average time %Lf10 secs\n",elapsed/reps);
        exit(0); //Need to return stuff, if you don't return 0 make will assume error
        //Returning 1 will make (or bash) not run stuff afterwards
}
~~~

We then compiled this program with all possible optimization levels and generated assembler. See the `makefile` below.

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



## Inlining

## Locality

## Indirect addressing

## Writing to HDD and to SSD

## Valgrind

## Profiling
