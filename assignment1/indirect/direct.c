#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void main(){
	int n=1000000;
	int m=1000;

	//Here a is a scalar and x, y are vectors.
	//Pick whatever you wish!
	int a;
	int *x=(int*)malloc(sizeof(int)*n);
	int *y=(int*)malloc(sizeof(int)*n);
	
	struct timespec start,stop;
	long double elapsed;
	//Picking ones, because why not?
	a=1;
	for(size_t i = 0; i < n; ++i){
		x[i]=1;
		y[i]=1;
	}

	//Variant 3
	//Why do
	//	int *p=(int*)malloc(sizeof(int)*n);
	//	for(size_t ix=0; ix < n; ++ix)
	//		p[ix]=ix;
	//when you can just access directly?
	
	timespec_get(&start,TIME_UTC);
	for(size_t kx = 0; kx < n; ++kx){
		y[kx] += a * x[kx];
	}
	timespec_get(&stop,TIME_UTC);
	elapsed=(stop.tv_sec+1.0e-9*stop.tv_nsec)-(start.tv_sec+1.0e-9*start.tv_nsec);
	printf("%Lf10 was the time it took.\n",elapsed);
	exit(0);
}
