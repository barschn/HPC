#include <pthread.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <gsl/gsl_complex.h>
#include <gsl/gsl_complex_math.h>

#define GLEVELS 15

#define X4 gsl_complex_rect(GSL_REAL(xprev)*GSL_REAL(xprev)*GSL_REAL(xprev)*GSL_REAL(xprev)-6*GSL_REAL(xprev)*GSL_REAL(xprev)*GSL_IMAG(xprev)*GSL_IMAG(xprev)+GSL_IMAG(xprev)*GSL_IMAG(xprev)*GSL_IMAG(xprev)*GSL_IMAG(xprev),4*(GSL_REAL(xprev)*GSL_REAL(xprev)*GSL_REAL(xprev)*GSL_IMAG(xprev)-GSL_REAL(xprev)*GSL_IMAG(xprev)*GSL_IMAG(xprev)*GSL_IMAG(xprev)))

#define X6 gsl_complex_rect(-1.0*GSL_IMAG(xprev)*GSL_IMAG(xprev)*GSL_IMAG(xprev)*GSL_IMAG(xprev)*GSL_IMAG(xprev)*GSL_IMAG(xprev)+15.0*GSL_IMAG(xprev)*GSL_IMAG(xprev)*GSL_IMAG(xprev)*GSL_IMAG(xprev)*GSL_REAL(xprev)*GSL_REAL(xprev)-15.0*GSL_IMAG(xprev)*GSL_IMAG(xprev)*GSL_REAL(xprev)*GSL_REAL(xprev)*GSL_REAL(xprev)*GSL_REAL(xprev)+GSL_REAL(xprev)*GSL_REAL(xprev)*GSL_REAL(xprev)*GSL_REAL(xprev)*GSL_REAL(xprev)*GSL_REAL(xprev),6.0*GSL_IMAG(xprev)*GSL_IMAG(xprev)*GSL_IMAG(xprev)*GSL_IMAG(xprev)*GSL_IMAG(xprev)*GSL_REAL(xprev)-20.0*GSL_IMAG(xprev)*GSL_IMAG(xprev)*GSL_IMAG(xprev)*GSL_REAL(xprev)*GSL_REAL(xprev)*GSL_REAL(xprev)+6.0*GSL_IMAG(xprev)*GSL_REAL(xprev)*GSL_REAL(xprev)*GSL_REAL(xprev)*GSL_REAL(xprev)*GSL_REAL(xprev))

int nthreads;
int lines;
int d;

pthread_mutex_t mutex_main;

unsigned char ** gi; //Gray image
unsigned char * gi_entries;

void n1(int m1, int m2){
	int iter=1;
	for(size_t flati=0; flati < lines*lines/nthreads; ++flati){
		gi[m1][m2] = (iter*GLEVELS)/200 % GLEVELS;
		m2 = (flati+1)%lines;
		m1= nthreads*((flati+1)/lines);
	}
}

void n2(int m1, int m2){
	int iter;
	double linesd = (double) lines;
	double xc = -2+4*m2/linesd+4/(2*linesd);
	double yc = -2+4*(linesd-1-m1)/linesd+4/(2*linesd);
	gsl_complex x, xprev;
	for(size_t flati=0; flati < lines*lines/nthreads; ++flati){
		xprev = gsl_complex_rect(xc,yc);
		x = gsl_complex_mul_real(gsl_complex_add(xprev,gsl_complex_inverse(xprev)),0.5);
		while(gsl_complex_abs(gsl_complex_sub(x,xprev))>=1e-3
				&& gsl_complex_abs(x)>=1e-3
				&& GSL_REAL(x)<1e10
				&& GSL_IMAG(x)<1e10){
			xprev=x;
			x = gsl_complex_mul_real(gsl_complex_add(xprev,gsl_complex_inverse(xprev)),0.5);
			iter++;
		}
		gi[m1][m2]=(iter*GLEVELS)/200 % GLEVELS;
		m2 = (flati+1) % lines;
		m1 = nthreads*((flati+1)/lines);
		xc = -2+4*m2/linesd+4/(2*linesd);
		yc = -2+4*(linesd-1-m1)/linesd+4/(2*linesd);
	}
}

void n3(int m1, int m2){
}

void n4(int m1, int m2){
}

void n5(int m1, int m2){
	int iter;
	double linesd = (double) lines;
	double xc = -2+4*m2/linesd+4/(2*linesd);
	double yc = -2+4*(linesd-1-m1)/linesd+4/(2*linesd);
	gsl_complex x, xprev;
	for(size_t flati=0; flati < lines*lines/nthreads; ++flati){
		xprev = gsl_complex_rect(xc,yc);
		x = gsl_complex_add(gsl_complex_mul_real(xprev,0.8),gsl_complex_mul_real(gsl_complex_inverse(X4),0.2));
		while(gsl_complex_abs(gsl_complex_sub(x,xprev))>=1e-3
				&& gsl_complex_abs(x)>=1e-3
				&& GSL_REAL(x)<1e10
				&& GSL_IMAG(x)<1e10){
			xprev=x;
			x = gsl_complex_add(gsl_complex_mul_real(xprev,0.8),gsl_complex_mul_real(gsl_complex_inverse(X4),0.2));
			iter++;
		}
		gi[m1][m2]=(iter*GLEVELS)/200 % GLEVELS;
		m2 = (flati+1) % lines;
		m1 = nthreads*((flati+1)/lines);
		xc = -2+4*m2/linesd+4/(2*linesd);
		yc = -2+4*(linesd-1-m1)/linesd+4/(2*linesd);
	}
}

void n6(int m1, int m2){
}

void n7(int m1, int m2){
	int iter;
	double linesd = (double) lines;
	double xc = -2+4*m2/linesd+4/(2*linesd);
	double yc = -2+4*(linesd-1-m1)/linesd+4/(2*linesd);
	gsl_complex x, xprev;
	for(size_t flati=0; flati < lines*lines/nthreads; ++flati){
		xprev = gsl_complex_rect(xc,yc);
		x = gsl_complex_add(gsl_complex_mul_real(xprev,0.8571428571428571),gsl_complex_mul_real(gsl_complex_inverse(X6),0.14285714285714285));
		while(gsl_complex_abs(gsl_complex_sub(x,xprev))>=1e-3
				&& gsl_complex_abs(x)>=1e-3
				&& GSL_REAL(x)<1e10
				&& GSL_IMAG(x)<1e10){
			xprev=x;
			x = gsl_complex_add(gsl_complex_mul_real(xprev,0.8571428571428571),gsl_complex_mul_real(gsl_complex_inverse(X6),0.14285714285714285));
			iter++;
		}
		gi[m1][m2]=(iter*GLEVELS)/200 % GLEVELS;
		m2 = (flati+1) % lines;
		m1 = nthreads*((flati+1)/lines);
		xc = -2+4*m2/linesd+4/(2*linesd);
		yc = -2+4*(linesd-1-m1)/linesd+4/(2*linesd);
	}
}

void nbig(int m1, int m2){
}

void *newton(void *arg){
	int * matc = (int *)arg;
	int mi = matc[0], mj = matc[1];	
	if (d == 1){
		n1(mi,mj);
	}else if(d == 2){
		n2(mi,mj);
	}else if(d == 3){
		n3(mi,mj);
	}else if(d == 4){
		n4(mi,mj);
	}else if(d == 5){
		n5(mi,mj);
	}else if(d == 6){
		n6(mi,mj);
	}else if(d == 7){
		n7(mi,mj);
	}else{
		//With gsl and a fast pow
		nbig(mi,mj);
	}	
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
	//	t0 ->
	//	t1 ->
	//	t2 ->
	//	t3 ->
	//	t4 ->
	//	t0 ->
	struct timespec start, stop;
	long double elapsed;
	timespec_get(&start, TIME_UTC);
	pthread_mutex_init(&mutex_main,NULL);
	//Creation
	for(t = 0; t < nthreads; ++t){
		int * coords = (int *)malloc(sizeof(int)*2);
		coords[0]=t;
		coords[1]=0;
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
	timespec_get(&stop, TIME_UTC);
	//Write to file
	FILE * file;
	file=fopen("grayscale.pgm","wb");
	fprintf(file,"P5\n%d %d\n%d\n",lines,lines,GLEVELS);
	fwrite(gi_entries,sizeof(unsigned char),lines*lines,file);
	fclose(file);
	free(gi_entries);
	free(gi);	
	elapsed = (stop.tv_sec+1e-9*stop.tv_nsec)-(start.tv_sec+1.0e-9*start.tv_nsec);
	printf("elapsed excl wr=%.15Lf secs\n",elapsed);
	return 0;
}
