#include <stdio.h>
#include <stdlib.h>
#include "mul_cpx_separatefile.h"
#include <time.h>

#define SIZE 30000

void main(){
	struct timespec start,stop;
	printf("This is separatefile. I multiply complex numbers together.\n");
	double * ares = (double *) malloc(sizeof(double)*SIZE);
	double * aims = (double *) malloc(sizeof(double)*SIZE);
	double * bres = (double *) malloc(sizeof(double)*SIZE);
	double * bims = (double *) malloc(sizeof(double)*SIZE);
	double * cres = (double *) malloc(sizeof(double)*SIZE);
	double * cims = (double *) malloc(sizeof(double)*SIZE);
	
	long double elapsed;
	
	timespec_get(&start, TIME_UTC);
	//Generating entries for b and c
	for (size_t i=0; i<SIZE; ++i){
		*(bres + i) = 1;
		*(bims + i) = 1;
		*(cres + i) = 1;
		*(cims + i) = 1;
	}
	timespec_get(&stop, TIME_UTC);
	elapsed=(stop.tv_sec+1.0e-9*stop.tv_nsec)-(start.tv_sec+1.0e-9*start.tv_nsec);
	printf("Took %Lf10 secs to generate.\n",elapsed);

	timespec_get(&start, TIME_UTC);
	for (size_t i=0; i<SIZE; ++i)
		mul_cpx_separatefile(ares+i, aims+i, bres+i, bims+i, cres+i, cims+i);
	timespec_get(&stop, TIME_UTC);
	elapsed=(stop.tv_sec+1.0e-9*stop.tv_nsec)-(start.tv_sec+1.0e-9*start.tv_nsec);
	printf("Took %Lf10 secs to compute.\n",elapsed);
	
	//printf("Printing results.\n");
	//for (size_t i=0; i<SIZE; ++i)
	//	printf("%lf + %lf*I\n",*(ares+i),*(aims+i));
	exit(0);
}
