#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 3

void main(){
	FILE * matrixfile;
	matrixfile=fopen("matrix.txt","w");
	int * asentries = (int*)malloc(sizeof(int)*SIZE*SIZE);
	int ** as = (int**)malloc(sizeof(int*)*SIZE); //Just for the comfort of double indices. Not in fact needed.
	//Don't forget to initialize! Otherwise we'll segfault.
	for (size_t ix=0, jx=0; ix<SIZE; ++ix,jx+=SIZE)
		as[ix]=asentries+jx;

	for (size_t ix=0; ix<SIZE; ++ix){
		for (size_t jx=0; jx<SIZE; ++jx){
			scanf("%d",&as[ix][jx]);
			fprintf(matrixfile,"%d ",as[ix][jx]);
		}
		printf("changing row\n");
		fprintf(matrixfile,"\n");
		fflush(matrixfile);
	}
	fclose(matrixfile);
	matrixfile=fopen("matrix.txt","r");
	int * current =(int*)malloc(sizeof(int));
	int areequal = 0;
	for (size_t ix=0; ix<SIZE; ++ix){
		for (size_t jx=0; jx<SIZE; ++jx){
			fscanf(matrixfile,"%d",current);
			areequal = *current == as[ix][jx];
			printf(areequal ? "are equal\n" : "aren't equal\n"); 
		}
	}
	fclose(matrixfile);
	free(as);
	free(asentries);
}	
