#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 10

//What happens if we're dumb, i. e. if we allocate memory non-contiguously?
//Answered by running this program.
void main(){
	FILE * matrixfile;
	matrixfile=fopen("matrix.txt","w");
	int ** as = (int**)malloc(sizeof(int*)*SIZE);
	
	//Allocating all over the place.
	for (size_t ix=0; ix<SIZE; ++ix)
		as[ix]=(int*) malloc(sizeof(int)*SIZE);

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
}	
