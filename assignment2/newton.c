#include <pthread.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <complex.h>

#define D 3

#define NUM_THREADS 10

#define SIZE 10 //This is the height and width of the picture, in pixels

pthread_mutex_t mutex_main; //Why though?

double ** pmat;
double *pmatentries;

//This is where we Newton
void *newton(void *arg){
	while(abs(x-xprev)>=1e-3){
		xprev=x;
		x=x-(x^D-1)/(D*x^(D-1));
	}

	return NULL;
}

int main(){
	//Scratch, will store colors
	//In final, try to keep on stack for speed
	pmat = (double **)malloc(sizeof(double *)*SIZE);
	pmatentries = (double *)malloc(sizeof(double)*SIZE*SIZE);
	for(size_t i=0, j=0; i < SIZE; ++i, j+=SIZE)
		pmat[i]=pmatentries+j;
	for(size_t i=0; i < SIZE*SIZE; ++i)
		pmatentries[i]=0;
	
	int ret;
	pthread_t threads[NUM_THREADS];
	size_t t;
	
	//Creation
	pthread_mutex_init(&mutex_main, NULL);
	for(t=0; t<NUM_THREADS; ++t){
		printf("Going to start t=%ld\n",t);
		double * coords = (double*)malloc(2*sizeof(double)); //Having it on the stack instead seems to not allocate in different places so that e. g. (x,y)=(0,0) will never be output
		coords[0]=(double) t;
		coords[1]=(double) t;
		//Passing (void*)t is threadsafe
		if(ret = pthread_create(threads+t, NULL, newton, (void*)coords)){
			printf("Error creating thread: %d\n", ret);
			exit(1);
		}
	}
	//Joining
	for(t=0; t<NUM_THREADS; ++t){
		if(ret = pthread_join(threads[t], NULL)){
			printf("Error joining thread: %d\n", ret);
			exit(1);
		}
	}
	pthread_mutex_destroy(&mutex_main);

	return 0;
}
