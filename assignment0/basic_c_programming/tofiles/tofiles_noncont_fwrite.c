#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10


//Seems to be no speed difference, is the conclusion that we have to write in a loop, which is slow?
void main(){
	FILE * matrixfile;
	struct timespec start,stop;
	long double elapsed;
	timespec_get(&start,TIME_UTC);
	matrixfile=fopen("matrix.bin","w");
	int ** as = (int**)malloc(sizeof(int*)*SIZE);
	int ** asread = (int**)malloc(sizeof(int*)*SIZE);
	
	for(size_t ix=0; ix<SIZE; ++ix){
		as[ix]=(int*)malloc(sizeof(int)*SIZE);
		asread[ix]=(int*)malloc(sizeof(int)*SIZE);
	}

	for (size_t ix=0; ix<SIZE; ++ix){
		for (size_t jx=0; jx<SIZE; ++jx){
			as[ix][jx]=ix*jx;
		}
	}
	for(size_t ix=0; ix<SIZE; ++ix)
		fwrite(as[ix], sizeof(int), SIZE, matrixfile);
	fclose(matrixfile);

	matrixfile=fopen("matrix.bin","r");
	for(size_t ix=0; ix<SIZE; ++ix)
		fread(asread[ix], sizeof(int), SIZE, matrixfile);
	int areequal = 1;
	for (size_t ix=0; ix<SIZE; ++ix){
		for (size_t jx=0; jx<SIZE; ++jx){
			areequal *= asread[ix][jx] == as[ix][jx];
		}
	}
	printf(areequal ? "are equal\n" : "aren't equal\n");
	fclose(matrixfile);
	for(size_t ix=0; ix<SIZE; ++ix){
		free(as[ix]);
		free(asread[ix]);
	}
	free(as);
	free(asread);
	timespec_get(&stop,TIME_UTC);
	elapsed=(stop.tv_sec+1.0e-9*stop.tv_nsec)-(start.tv_sec+1.0e-9*start.tv_nsec);
	printf("Total time %.15Lf secs\n",elapsed);
	exit(0);
}	
