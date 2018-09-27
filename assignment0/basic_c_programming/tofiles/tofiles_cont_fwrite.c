#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10

void main(){
	FILE * matrixfile;
	struct timespec start,stop;
	long double elapsed;
	timespec_get(&start,TIME_UTC);
	matrixfile=fopen("matrix.bin","w");
	int ** as = (int**)malloc(sizeof(int*)*SIZE);
	int * asentries = (int*)malloc(sizeof(int)*SIZE*SIZE);
	int ** asread = (int**)malloc(sizeof(int*)*SIZE);
	int * asreadentries = (int*)malloc(sizeof(int)*SIZE*SIZE);
	
	for(size_t ix=0, jx=0; ix<SIZE; ++ix, jx+=SIZE){
		as[ix]=asentries+jx;
		asread[ix]=asreadentries+jx;
	}

	for (size_t ix=0; ix<SIZE; ++ix){
		for (size_t jx=0; jx<SIZE; ++jx){
			as[ix][jx]=ix*jx;
		}
	}
	fwrite(asentries, sizeof(int), SIZE*SIZE, matrixfile);
	fclose(matrixfile);

	matrixfile=fopen("matrix.bin","r");
	fread(asreadentries, sizeof(int), SIZE*SIZE, matrixfile);
	int areequal = 1;
	for (size_t ix=0; ix<SIZE; ++ix){
		for (size_t jx=0; jx<SIZE; ++jx){
			areequal *= asread[ix][jx] == as[ix][jx];
		}
	}
	printf(areequal ? "are equal\n" : "aren't equal\n");
	fclose(matrixfile);
	free(as);
	free(asentries);
	free(asread);
	free(asreadentries);
	timespec_get(&stop,TIME_UTC);
	elapsed=(stop.tv_sec+1.0e-9*stop.tv_nsec)-(start.tv_sec+1.0e-9*start.tv_nsec);
	printf("Total time %.15Lf secs\n",elapsed);
	exit(0);
}	
