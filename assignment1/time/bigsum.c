#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define SIZE 1000000000

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
