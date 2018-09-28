#include <pthread.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <tgmath.h>
#include <complex.h>

int d;

#define NUM_THREADS 9

#define SIZE 10 //This is the height and width of the picture, in pixels

pthread_mutex_t mutex_main; //Why though?

double ** pmat;
double *pmatentries;

//This is where we Newton
void *newton(void *arg){
	//Converting from matrix coordinate to input
	int * matc = (int *) arg;
	double blocksize = (double) d;
	printf("(%d,%d) start\n",matc[0],matc[1]);
	double xc = -2+4*matc[1]/blocksize+4/(2*blocksize);
	printf("xc=%lf\n",xc);
	double yc = -2+4*(blocksize-1-matc[0])/blocksize+4/(2*blocksize);
	printf("yc=%lf\n",yc);
	printf("(%d,%d) converts to %lf+I*%lf\n",matc[0],matc[1],xc,yc);

	//Initializing Newton
	double complex xprev = xc + I*yc;
	double complex x=xprev-(pow(xprev,d)-1)/(d*pow(xprev,d-1));
	//Running Newton
	while(cabs(x-xprev)>=1e-3){
		xprev=x;
		x=xprev-(pow(xprev,d)-1)/(d*pow(xprev,d-1));
	}
	printf("%lf+I*%lf\n stopped at %lf+I*%lf\n",xc,yc,creal(x),cimag(x));
	return NULL;
}

int main(int argc, char * argv[]){
	d=(int) strtol(argv[1],NULL,10);
	//Scratch, will store colors
	//In final, try to keep on stack for speed
	pmat = (double **)malloc(sizeof(double *)*SIZE);
	pmatentries = (double *)malloc(sizeof(double)*SIZE*SIZE);
	for(size_t i=0, j=0; i < SIZE; ++i, j+=SIZE)
		pmat[i]=pmatentries+j;
	for(size_t i=0; i < SIZE*SIZE; ++i)
		pmatentries[i]=0;

	int ret; //Error flag
	pthread_t threads[NUM_THREADS]; //My threads
	size_t t; //Thread counter
	
	//Creation
	pthread_mutex_init(&mutex_main, NULL); //Could be useful
	//Scratch, testing with 3x3 matrix first
	for(t=0; t<NUM_THREADS; ++t){
		printf("start t=%ld\n",t);
		int * coords = (int *)malloc(sizeof(int)*2);
		coords[0]=t/3;
		coords[1]=t%3;
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
