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

	//Allocating and generating p
	int *p=(int*)malloc(sizeof(int)*n);
	size_t ix = 0;
	for(size_t jx = 0; jx < m; ++jx)
		for(size_t kx = 0; kx < m; ++kx)
			p[jx + m*kx] = ix++;
	
	timespec_get(&start,TIME_UTC);
	int j;
	for(size_t kx = 0; kx < n; ++kx){
		j=p[kx];
		y[j] += a * x[j];
	}
	timespec_get(&stop,TIME_UTC);
	elapsed=(stop.tv_sec+1.0e-9*stop.tv_nsec)-(start.tv_sec+1.0e-9*start.tv_nsec);
	printf("%Lf10 was the time it took.\n",elapsed);
	exit(0);
}
