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

We see that on average `-O3` is fastest. Note also that for `-O2`, `-O3`, and `-Os`, we often get individual loop times equal to zero -- let's get back to this later. Ordering the optimization levels by average execution time (of the program) we get

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

Let's delve a bit deeper into the actual timing, by compiling with the debug flag `-g` and then using `gdb`. Run

~~~bash
[tobias@gantenbein time]$ gcc -O3 -g bigsum.c -o bigsum_opt3_debug
~~~

and then

~~~bash
[tobias@gantenbein time]$ gdb -tui bigsum_opt3_debug
~~~

In `gdb`, we can then run

~~~bash
(gdb) layout split
(gdb) break main
Breakpoint 1 at 0x400500: file bigsum.c, line 10.
(gdb)
~~~

We now get an **extraordinarily** nice view of what is being executed -- both in the assembler code and in the actual C code. Running `run 3` and stepping instruction-wise a few times we see the precise reason why `-O3` is so fast!

~~~
   ┌──bigsum.c─────────────────────────────────────────────────────────────────────────────────────────┐
B+ │10              int reps=strtol(argv[1],NULL,10);                                                  │
   │11              long double elapsed;                                                               │
   │12              timespec_get(&absstart, TIME_UTC);                                                 │
  >│13              for(size_t n=0; n<reps; ++n){                                                      │
   │14                      timespec_get(&start, TIME_UTC);                                            │
   │15                      for(size_t i=0; i<SIZE; ++i)                                               │
   │16                              S+=i;                                                              │
   │17                      timespec_get(&stop, TIME_UTC);                                             │
   │18                      printf("Result: %ld\n",S);                                                 │
   │19                      elapsed=(stop.tv_sec+1.0e-9*stop.tv_nsec)-(start.tv_sec+1.0e-9*start.tv_nse│
   │20                      printf("Took %.15Lf secs\n",elapsed);                                      │
   │21                      S=0;                                                                       │
   │22              }                                                                                  │
   │23              timespec_get(&absstop, TIME_UTC);                                                  │
   │24              elapsed=(absstop.tv_sec+1.0e-9*absstop.tv_nsec)-(absstart.tv_sec+1.0e-9*absstart.tv│
   │25              printf("Total time %.15Lf secs\n",elapsed);                                        │
   │26              printf("Average time %.15Lf secs\n",elapsed/reps);                                 │
   │27              exit(0); //Need to return stuff, if you don't return 0 make will assume error      │
   │28              //Returning 1 will make (or bash) not run stuff afterwards                         │
   ┌───────────────────────────────────────────────────────────────────────────────────────────────────┐
   │0x40051d <main+29>      lea    0x40(%rsp),%rdi                                                     │
   │0x400522 <main+34>      mov    %rax,%rbp                                                           │
   │0x400525 <main+37>      mov    %eax,0x1c(%rsp)                                                     │
   │0x400529 <main+41>      callq  0x4004c0 <timespec_get@plt>                                         │
   │0x40052e <main+46>      movslq %ebp,%rbp                                                           │
   │0x400531 <main+49>      test   %rbp,%rbp                                                           │
   │0x400534 <main+52>      je     0x400693 <main+403>                                                 │
   │0x40053a <main+58>      movsd  0x336(%rip),%xmm6        # 0x400878                                 │
   │0x400542 <main+66>      xor    %ebx,%ebx                                                           │
  >│0x400544 <main+68>      movabs $0x6f05b59b5e49b00,%r12                                             │
   │0x40054e <main+78>      movsd  %xmm6,0x10(%rsp)                                                    │
   │0x400554 <main+84>      lea    0x20(%rsp),%rdi                                                     │
   │0x400559 <main+89>      mov    $0x1,%esi                                                           │
   │0x40055e <main+94>      add    $0x1,%rbx                                                           │
   │0x400562 <main+98>      callq  0x4004c0 <timespec_get@plt>                                         │
   │0x400567 <main+103>     lea    0x30(%rsp),%rdi                                                     │
   │0x40056c <main+108>     mov    $0x1,%esi                                                           │
   │0x400571 <main+113>     callq  0x4004c0 <timespec_get@plt>                                         │
   │0x400576 <main+118>     mov    %r12,%rsi                                                           │
   └───────────────────────────────────────────────────────────────────────────────────────────────────┘
native process 11775 In: main                                                        L13   PC: 0x400544 


(gdb) b	main
Breakpoint 1 at 0x400500: file bigsum.c, line 10.
(gdb) run 3
Starting program: /home/tobias/GIT/HPC/assignment1/time/bigsum_opt3_debug 3
Missing separate debuginfos, use: dnf debuginfo-install glibc-2.27-30.fc28.x86_64

Breakpoint 1, main (argc=2, argv=0x7fffffffdf68) at bigsum.c:10
(gdb) n
(gdb) ni
(gdb) ni
(gdb) ni
(gdb) ni
(gdb) ni
(gdb) ni
(gdb) 
~~~

Of special importance is the instruction at `0x400544 <main+68>`.

~~~asm
movabs $0x6f05b59b5e49b00,%r12
~~~

Converting `0x6f05b59b5e49b00` to `long`, we get 499999999500000000. But this is just $$\frac{(10^9-1)\cdot 10^9}{2}$$, i. e. the sum of the first billion integers. The compiler precomputes the sum!

This does indeed not happen when compiling with `-O0`, see below.

~~~
   ┌──bigsum.c──────────────────────────────────────────────────────┐
   │7       void main(int argc, char *argv[]){                      │
   │8               struct timespec start,stop,absstart,absstop;    │
   │9               long S=0;                                       │
   │10              int reps=strtol(argv[1],NULL,10);               │
   │11              long double elapsed;                            │
   │12              timespec_get(&absstart, TIME_UTC);              │
   │13              for(size_t n=0; n<reps; ++n){                   │
   │14                      timespec_get(&start, TIME_UTC);         │
B+ │15                      for(size_t i=0; i<SIZE; ++i)            │
  >│16                              S+=i;                           │
   │17                      timespec_get(&stop, TIME_UTC);          │
   │18                      printf("Result: %ld\n",S);              │
   │19                      elapsed=(stop.tv_sec+1.0e-9*stop.tv_nsec│
   │20                      printf("Took %.15Lf secs\n",elapsed);   │
   │21                      S=0;                                    │
   │22              }                                               │
   │23              timespec_get(&absstop, TIME_UTC);               │
   │24              elapsed=(absstop.tv_sec+1.0e-9*absstop.tv_nsec)-│
   │25              printf("Total time %.15Lf secs\n",elapsed);     │
   ┌────────────────────────────────────────────────────────────────┐
   │0x400629 <main+67>      mov    %rax,%rdi                        │
   │0x40062c <main+70>      callq  0x4004c0 <timespec_get@plt>      │
   │0x400631 <main+75>      movq   $0x0,-0x10(%rbp)                 │
   │0x400639 <main+83>      jmpq   0x40071d <main+311>              │
   │0x40063e <main+88>      lea    -0x40(%rbp),%rax                 │
   │0x400642 <main+92>      mov    $0x1,%esi                        │
   │0x400647 <main+97>      mov    %rax,%rdi                        │
   │0x40064a <main+100>     callq  0x4004c0 <timespec_get@plt>      │
B+ │0x40064f <main+105>     movq   $0x0,-0x18(%rbp)                 │
   │0x400657 <main+113>     jmp    0x40066d <main+135>              │
  >│0x400659 <main+115>     mov    -0x8(%rbp),%rdx                  │
   │0x40065d <main+119>     mov    -0x18(%rbp),%rax                 │
   │0x400661 <main+123>     add    %rdx,%rax                        │
   │0x400664 <main+126>     mov    %rax,-0x8(%rbp)                  │
   │0x400668 <main+130>     addq   $0x1,-0x18(%rbp)                 │
   │0x40066d <main+135>     cmpq   $0x3b9ac9ff,-0x18(%rbp)          │
   │0x400675 <main+143>     jbe    0x400659 <main+115>              │
   │0x400677 <main+145>     lea    -0x50(%rbp),%rax                 │
   │0x40067b <main+149>     mov    $0x1,%esi                        │
   └────────────────────────────────────────────────────────────────┘
native process 12272 In: main                     L16   PC: 0x400659 


(gdb) b	15
Breakpoint 1 at 0x40064f: file bigsum.c, line 15.
(gdb) run 3
Starting program: /home/tobias/GIT/HPC/assignment1/time/bigsum_opt0_d
ebug 3
Missing separate debuginfos, use: dnf debuginfo-install glibc-2.27-30
.fc28.x86_64

Breakpoint 1, main (argc=2, argv=0x7fffffffdf68) at bigsum.c:15
(gdb) ni
(gdb) ni
(gdb) ni
(gdb) ni
(gdb)
~~~

Here we see that indeed the `for` loop is being executed. See the commented code below.

~~~
0x40064f <main+105>     movq   $0x0,-0x18(%rbp) //initialize i to 0
0x400657 <main+113>     jmp    0x40066d <main+135> //jump to the comparison
0x400659 <main+115>     mov    -0x8(%rbp),%rdx //loop: put S in %rdx
0x40065d <main+119>     mov    -0x18(%rbp),%rax //put i in %rax
0x400661 <main+123>     add    %rdx,%rax //add %rdx and %rax and store result in %rax
0x400664 <main+126>     mov    %rax,-0x8(%rbp) //move %rax to S
0x400668 <main+130>     addq   $0x1,-0x18(%rbp) //add 1 to i
0x40066d <main+135>     cmpq   $0x3b9ac9ff,-0x18(%rbp) //comparison: comparing i with 0x3b9ac9ff=999999999
0x400675 <main+143>     jbe    0x400659 <main+115> //jump to the loop if below or equal
~~~

I don't have time to look at the other assembler code in detail, even if it'd be delightful.

## Inlining

## Locality

## Indirect addressing

## Writing to HDD and to SSD

## Valgrind

## Profiling
