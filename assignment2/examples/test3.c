#include <pthread.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <tgmath.h>
#include <complex.h>

#define GLEVELS 15

int nthreads;
int lines;
int d;

pthread_mutex_t mutex_main;

unsigned char ** gi; //Gray image
unsigned char * gi_entries;


//Very slow, adjust to so that it doesn't stop after one convergence
void *newton(void *arg){
	int * matc = (int *)arg;
	double linesd = (double) lines;
	double xc = -2+4*matc[1]/linesd+4/(2*linesd);
	double yc = -2+4*(linesd-1-matc[0])/linesd+4/(2*linesd);
	//printf("at (%d,%d) |-> %lf+I*%lf\n",matc[0],matc[1],xc,yc);
	double complex xprev = xc + I*yc;
	double complex x = xprev-(pow(xprev,d)-1)/(d*pow(xprev,d-1));
	size_t iter=0;
	while(cabs(x-xprev)>=1e-3 && cabs(x)>=1e-3 && creal(x)<1e10 && cimag(x)<1e10){
		xprev=x;
		x=xprev-(pow(xprev,d)-1)/(d*pow(xprev,d-1));
		iter++;
	}
	//printf("at (%d,%d) converged to %lf+I*%lf\n",matc[0],matc[1],creal(x),cimag(x));
	//Doing stuff with iter and x
	//Ugly, will change
	gi[matc[0]][matc[1]]=(iter*GLEVELS)/200 % GLEVELS;
	return NULL;
}

int main(int argc, char *argv[]){
	nthreads = (int)strtol(argv[1]+2,NULL,10);
	lines = (int)strtol(argv[2]+2,NULL,10);
	d = (int)strtol(argv[3],NULL,10);
	printf("nthreads = %d, lines = %d, d = %d\n",nthreads,lines,d);
	gi = (unsigned char **)malloc(sizeof(char*)*lines);
	gi_entries = (unsigned char *)malloc(sizeof(char)*lines*lines);
	for(size_t i=0, j=0; i < lines; ++i, j+=lines)
		gi[i]=gi_entries+j;
	for(size_t i=0; i < lines*lines; ++i)
		gi_entries[i]=(unsigned char)0;

	int ret;
	pthread_t threads[nthreads];
	size_t t;

	int q = lines/nthreads;

	//Draft: Strategy
	//	c1(t1 t2 t3 t4 t5) c2(t1 t2 t3 t4 t5) .  .  .
	//	c1(t1 t2 t3 t4 t5) c2(t1 t2 t3 t4 t5) .  .  .
	//	.                  .
	//	.                  .
	//	.                  .
	for(size_t row = 0; row < lines; ++row){
		for(size_t chunk = 0; chunk < q; ++chunk){
			//Creation
			pthread_mutex_init(&mutex_main, NULL);
			for(t = 0; t < nthreads; ++t){
				int * coords = (int *)malloc(sizeof(int)*2);
				//Fill in the coords
				coords[0]=row;
				coords[1]=nthreads*chunk+t;
				if(ret = pthread_create(threads+t, NULL, newton, (void*)coords)){
					printf("Error creating thread: %d\n", ret);
					exit(1);
				}
			}
			//Joining
			for(t = 0; t < nthreads; ++t){
				if(ret = pthread_join(threads[t], NULL)){
					printf("Error joining thread: %d\n", ret);
					exit(1);
				}
			}
			pthread_mutex_destroy(&mutex_main);
		}
	}
	//Write to file
	FILE * file;
	file=fopen("grayscale.pgm","wb");
	fprintf(file,"P5\n%d %d\n%d\n",lines,lines,GLEVELS);
	fwrite(gi_entries,sizeof(unsigned char),lines*lines,file);
	fclose(file);
	return 0;
}
