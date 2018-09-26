#include <pthread.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define D 3

#define NUM_THREADS 10

#define SIZE 10 //This is the height and width of the picture, in pixels

pthread_mutex_t mutex_main; //Why though?

//Scratch, will store colors
//In final, try to keep on stack for speed
double ** pmat = (double **)malloc(sizeof(double *)*SIZE);
double * pmatentries = (double *)malloc(sizeof(double)*SIZE);
for(size_t i=0, j=0; i < SIZE; ++i, j+=SIZE)
	pmat[i]=pmatentries+j;

//This is where we Newton
void *newton(void *arg){
	return NULL;
}

int main(){
	int ret;
	pthread_t threads[NUM_THREADS];
	size_t t;
	
	//Creation
	pthread_mutex_init(&mutex_main, NULL);
	for(t=0; tx<NUM_THREADS; ++t){
		if(ret = pthread_create(threads+tx, NULL, dotprod, NULL)){
			printf("Error creating thread: %d\n", ret);
			exit(1);
		}
	}
	//Joining
	for(t=0; t<NUM_THREADS; ++t){
		if(ret = pthread(threads_join[tx], NULL)){
			printf("Error joining thread: %d\n", ret);
			exit(1);
		}
	}
	pthread_mutex_destroy(&mutex_sum);

	return 0;
}
