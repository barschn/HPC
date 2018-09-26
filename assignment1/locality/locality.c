#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1000
#define ITER 1000


//Was const double **, but that didn't work
void row_sums(double * sums, const double ** matrix, size_t nrs, size_t ncs){
  for ( size_t ix=0; ix < nrs; ++ix ) {
    double sum = 0;
    for ( size_t jx=0; jx < ncs; ++jx )
      sum += matrix[ix][jx];
    sums[ix] = sum;
  }
}

//Was const double **, but that didn't work
void col_sums(double * sums, const double ** matrix, size_t nrs, size_t ncs){
  for ( size_t jx=0; jx < ncs; ++jx ) {
    double sum = 0;
    for ( size_t ix=0; ix < nrs; ++ix )
      sum += matrix[ix][jx];
    sums[jx] = sum;
  }
}

void main(){
	struct timespec start,stop;
	long double elapsed;
	//fmatrix = flat matrix
	double * fmat = (double *)malloc(sizeof(double)*SIZE*SIZE);
	//Was
	//const double ** mat = (const double **)malloc(sizeof(double*)*SIZE);
	//But then I couldn't change the values
	const double ** mat = (const double **)malloc(sizeof(double*)*SIZE);
		
	//Row major order, i. e.
	//a11 a12 a13 a21 a22 a23 a31 a32 a33
	//for SIZE=3
	
	for (size_t i = 0, j=0; i<SIZE; ++i, j+=SIZE)
		mat[i] = fmat + j;
	//Filling the matrix with ones, because why not?
	for (size_t i = 0; i<SIZE*SIZE; ++i)
		fmat[i]=1;
	
	double * sums = (double *)malloc(sizeof(double)*SIZE);
	
	timespec_get(&start,TIME_UTC);
	for(size_t k=0; k < ITER; ++k){	
		row_sums(sums, mat, SIZE, SIZE);	
	}
	timespec_get(&stop,TIME_UTC);
	elapsed = (stop.tv_sec+1.0e-9*stop.tv_nsec)-(start.tv_sec+1.0e-9*start.tv_nsec);
	printf("%Lf10 secs for row sums.\n",elapsed/ITER);
	
	timespec_get(&start,TIME_UTC);
	for(size_t k=0; k < ITER; ++k){
		col_sums(sums, mat, SIZE, SIZE);
	}
	timespec_get(&stop,TIME_UTC);
	elapsed = (stop.tv_sec+1.0e-9*stop.tv_nsec)-(start.tv_sec+1.0e-9*start.tv_nsec);
	printf("%Lf10 secs for col sums.\n",elapsed/ITER);
	
	exit(0);
}	
