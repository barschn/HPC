#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1000

void row_sums(double * sums, const double ** matrix, size_t nrs, size_t ncs){
  for ( size_t ix=0; ix < nrs; ++ix ) {
    double sum = 0;
    for ( size_t jx=0; jx < ncs; ++jx )
      sum += matrix[ix][jx];
    sums[ix] = sum;
  }
}

void col_sums(double * sums, const double ** matrix, size_t nrs, size_t ncs){
  for ( size_t jx=0; jx < ncs; ++jx ) {
    double sum = 0;
    for ( size_t ix=0; ix < nrs; ++ix )
      sum += matrix[ix][jx];
    sums[jx] = sum;
  }
}

//This should be faster as it accesses the memory linearly
//We do however look up csums quite often, so maybe not
void rowcol_sums(double *rsums, double *csums, const double ** matrix, size_t nrs, size_t ncs){
	double current;
	//double sum = 0;
	//double * sum = (double *)malloc(ncs*sizeof(double));
	for (size_t ix=0; ix<nrs; ++ix){
		for(size_t jx=0; jx<ncs; ++jx){
			current = matrix[ix][jx];//Removing this should make it faster b. c. vectorization
			//sum += current;//See above. 
			csums[jx] += current;
		}
		//rsums[ix]=sum;
		//sum=0;
	}
}

void main(){
	struct timespec start,stop;
	long double elapsed;
	//fmatrix = flat matrix
	double * fmat = (double *)malloc(sizeof(double)*SIZE*SIZE);	
	const double ** mat = (const double **)malloc(sizeof(double*)*SIZE); //Kan inte ändra härifrån det som står på adressen. Så mat[i][j]=1 är ogiltigt. Men får ändra på pointern mat[i].
	//Är det samma för const double *** o. s. v. Alltså att mat[i], mat[j] kan ändras, men inte mat[i][j][k]?
			
	//Row major order, i. e.
	//a11 a12 a13 a21 a22 a23 a31 a32 a33
	//for SIZE=3
	
	for (size_t i = 0, j=0; i<SIZE; ++i, j+=SIZE)
		mat[i] = fmat + j;
	//Filling the matrix with ones, because why not?
	for (size_t k = 0; k<SIZE*SIZE; ++k)
		*(fmat+k)=1;
	
	double * sums = (double *)malloc(sizeof(double)*SIZE);
	double * sums2 = (double *)malloc(sizeof(double)*SIZE);

	timespec_get(&start,TIME_UTC);
	row_sums(sums, mat, SIZE, SIZE);
	timespec_get(&stop,TIME_UTC);
	elapsed = (stop.tv_sec+1.0e-9*stop.tv_nsec)-(start.tv_sec+1.0e-9*start.tv_nsec);
	printf("%Lf10 secs for row sums.\n",elapsed);
	
	timespec_get(&start,TIME_UTC);
	col_sums(sums, mat, SIZE, SIZE);
	timespec_get(&stop,TIME_UTC);
	elapsed = (stop.tv_sec+1.0e-9*stop.tv_nsec)-(start.tv_sec+1.0e-9*start.tv_nsec);
	printf("%Lf10 secs for col sums.\n",elapsed);
	
	timespec_get(&start,TIME_UTC);
	rowcol_sums(sums, sums2, mat, SIZE, SIZE);
	timespec_get(&stop,TIME_UTC);
	elapsed = (stop.tv_sec+1.0e-9*stop.tv_nsec)-(start.tv_sec+1.0e-9*start.tv_nsec);
	printf("%Lf10 secs for row col sums.\n",elapsed);
	
	exit(0);
}	
