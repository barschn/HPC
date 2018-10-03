#include <pthread.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <gsl/gsl_complex.h>
#include <gsl/gsl_complex_math.h>
#include <gsl/gsl_math.h>

#define GLEVELS 255
#define GMAXITER 200

#define X2 gsl_complex_rect(GSL_REAL(xprev)*GSL_REAL(xprev)-GSL_IMAG(xprev)*GSL_IMAG(xprev),2*GSL_REAL(xprev)*GSL_IMAG(xprev))

#define X4 gsl_complex_rect(GSL_REAL(xprev)*GSL_REAL(xprev)*GSL_REAL(xprev)*GSL_REAL(xprev)-6*GSL_REAL(xprev)*GSL_REAL(xprev)*GSL_IMAG(xprev)*GSL_IMAG(xprev)+GSL_IMAG(xprev)*GSL_IMAG(xprev)*GSL_IMAG(xprev)*GSL_IMAG(xprev),4*(GSL_REAL(xprev)*GSL_REAL(xprev)*GSL_REAL(xprev)*GSL_IMAG(xprev)-GSL_REAL(xprev)*GSL_IMAG(xprev)*GSL_IMAG(xprev)*GSL_IMAG(xprev)))

#define X6 gsl_complex_rect(-1.0*GSL_IMAG(xprev)*GSL_IMAG(xprev)*GSL_IMAG(xprev)*GSL_IMAG(xprev)*GSL_IMAG(xprev)*GSL_IMAG(xprev)+15.0*GSL_IMAG(xprev)*GSL_IMAG(xprev)*GSL_IMAG(xprev)*GSL_IMAG(xprev)*GSL_REAL(xprev)*GSL_REAL(xprev)-15.0*GSL_IMAG(xprev)*GSL_IMAG(xprev)*GSL_REAL(xprev)*GSL_REAL(xprev)*GSL_REAL(xprev)*GSL_REAL(xprev)+GSL_REAL(xprev)*GSL_REAL(xprev)*GSL_REAL(xprev)*GSL_REAL(xprev)*GSL_REAL(xprev)*GSL_REAL(xprev),6.0*GSL_IMAG(xprev)*GSL_IMAG(xprev)*GSL_IMAG(xprev)*GSL_IMAG(xprev)*GSL_IMAG(xprev)*GSL_REAL(xprev)-20.0*GSL_IMAG(xprev)*GSL_IMAG(xprev)*GSL_IMAG(xprev)*GSL_REAL(xprev)*GSL_REAL(xprev)*GSL_REAL(xprev)+6.0*GSL_IMAG(xprev)*GSL_REAL(xprev)*GSL_REAL(xprev)*GSL_REAL(xprev)*GSL_REAL(xprev)*GSL_REAL(xprev))

int nthreads;
int lines;
int d;

//third roots of unity
gsl_complex z3_0;
gsl_complex z3_1;
gsl_complex z3_2;

//fifth roots of unity
gsl_complex z5_0;
gsl_complex z5_1;
gsl_complex z5_2;
gsl_complex z5_3;
gsl_complex z5_4;

//seventh roots of unity
gsl_complex z7_0;
gsl_complex z7_1;
gsl_complex z7_2;
gsl_complex z7_3;
gsl_complex z7_4;
gsl_complex z7_5;
gsl_complex z7_6;

pthread_mutex_t mutex_main;

unsigned char ** gi; //Gray image
unsigned char * gi_entries;

int ** ci; //RGB image
int * ci_entries;

int notisclose2(gsl_complex x){
	if((abs(GSL_REAL(x)-1)>=1e-3 || abs(GSL_IMAG(x))>=1e-3) 
			&& (abs(GSL_REAL(x)+1)>=1e-3 || abs(GSL_IMAG(x))>=1e-3)){
		return 1;
	}else if(gsl_complex_abs2(gsl_complex_add_real(x,-1.0))>=1e-6 
			&& gsl_complex_abs2(gsl_complex_add_real(x,1.0))>=1e-6){
		return 1;
	}else{
		return 0;
	}
}

int notisclose3(gsl_complex x){
	if((abs(GSL_REAL(x)-GSL_REAL(z3_0)) >= 1e-3 || abs(GSL_IMAG(x)-GSL_IMAG(z3_0)) >= 1e-3)
			&& (abs(GSL_REAL(x)-GSL_REAL(z3_1)) >= 1e-3 || abs(GSL_IMAG(x)-GSL_IMAG(z3_1)) >= 1e-3)
			&& (abs(GSL_REAL(x)-GSL_REAL(z3_2)) >= 1e-3 || abs(GSL_IMAG(x)-GSL_IMAG(z3_2)) >= 1e-3)){
		return 1;
	}else if(gsl_complex_abs2(gsl_complex_sub(x,z3_0))>=1e-6
			&& gsl_complex_abs2(gsl_complex_sub(x,z3_1))>=1e-6
			&& gsl_complex_abs2(gsl_complex_sub(x,z3_2))>=1e-6){
		return 1;
	}else{
		return 0;
	}
	
}

int notisclose4(gsl_complex x){
	return 1;
}

int notisclose5(gsl_complex x){
	if((abs(GSL_REAL(x)-GSL_REAL(z5_0)) >= 1e-3 || abs(GSL_IMAG(x)-GSL_IMAG(z5_0)) >= 1e-3)
			&& (abs(GSL_REAL(x)-GSL_REAL(z5_1)) >= 1e-3 || abs(GSL_IMAG(x)-GSL_IMAG(z5_1)) >= 1e-3)
			&& (abs(GSL_REAL(x)-GSL_REAL(z5_2)) >= 1e-3 || abs(GSL_IMAG(x)-GSL_IMAG(z5_2)) >= 1e-3)
			&& (abs(GSL_REAL(x)-GSL_REAL(z5_3)) >= 1e-3 || abs(GSL_IMAG(x)-GSL_IMAG(z5_3)) >= 1e-3)
			&& (abs(GSL_REAL(x)-GSL_REAL(z5_4)) >= 1e-3 || abs(GSL_IMAG(x)-GSL_IMAG(z5_4)) >= 1e-3)){
		return 1;
	}else if(gsl_complex_abs2(gsl_complex_sub(x,z5_0))>=1e-6
			&& gsl_complex_abs2(gsl_complex_sub(x,z5_1))>=1e-6
			&& gsl_complex_abs2(gsl_complex_sub(x,z5_2))>=1e-6
			&& gsl_complex_abs2(gsl_complex_sub(x,z5_3))>=1e-6
			&& gsl_complex_abs2(gsl_complex_sub(x,z5_4))>=1e-6){
		return 1;
	}else{
		return 0;
	}
}

int notisclose6(gsl_complex x){
	return 1;
}

int notisclose7(gsl_complex x){
	if((abs(GSL_REAL(x)-GSL_REAL(z7_0)) >= 1e-3 || abs(GSL_IMAG(x)-GSL_IMAG(z7_0)) >= 1e-3)
			&& (abs(GSL_REAL(x)-GSL_REAL(z7_1)) >= 1e-3 || abs(GSL_IMAG(x)-GSL_IMAG(z7_1)) >= 1e-3)
			&& (abs(GSL_REAL(x)-GSL_REAL(z7_2)) >= 1e-3 || abs(GSL_IMAG(x)-GSL_IMAG(z7_2)) >= 1e-3)
			&& (abs(GSL_REAL(x)-GSL_REAL(z7_3)) >= 1e-3 || abs(GSL_IMAG(x)-GSL_IMAG(z7_3)) >= 1e-3)
			&& (abs(GSL_REAL(x)-GSL_REAL(z7_4)) >= 1e-3 || abs(GSL_IMAG(x)-GSL_IMAG(z7_4)) >= 1e-3)
			&& (abs(GSL_REAL(x)-GSL_REAL(z7_5)) >= 1e-3 || abs(GSL_IMAG(x)-GSL_IMAG(z7_5)) >= 1e-3)
			&& (abs(GSL_REAL(x)-GSL_REAL(z7_6)) >= 1e-3 || abs(GSL_IMAG(x)-GSL_IMAG(z7_6)) >= 1e-3)){
		return 1;
	}else if(gsl_complex_abs2(gsl_complex_sub(x,z7_0))>=1e-6
			&& gsl_complex_abs2(gsl_complex_sub(x,z7_1))>=1e-6
			&& gsl_complex_abs2(gsl_complex_sub(x,z7_2))>=1e-6
			&& gsl_complex_abs2(gsl_complex_sub(x,z7_3))>=1e-6
			&& gsl_complex_abs2(gsl_complex_sub(x,z7_4))>=1e-6
			&& gsl_complex_abs2(gsl_complex_sub(x,z7_5))>=1e-6
			&& gsl_complex_abs2(gsl_complex_sub(x,z7_6))>=1e-6){
		return 1;
	}else{
		return 0;
	}
}

int notisclosebig(gsl_complex x){
	return 1;
}

void n1(int t){
	//Everything converges to 1, so don't do anything.	
}

void n2(int t){
	int iter,maxiter;
	maxiter = 0;
	double linesd = (double) lines;
	int m1, m2;
	double xc, yc;
	gsl_complex x, xprev;
	for(size_t flati=0; flati < lines*(lines/nthreads); ++flati){
		m2 = flati % lines;
		m1 = t+(flati/lines)*nthreads;
		xc = -2+4*m2/linesd+4/(2*linesd);
		yc = -2+4*(linesd-1-m1)/linesd+4/(2*linesd);
		xprev = gsl_complex_rect(xc,yc);
		x = gsl_complex_mul_real(gsl_complex_add(xprev,gsl_complex_inverse(xprev)),0.5);
		while(notisclose2(x) && gsl_complex_abs2(x)>=1e-6 && GSL_REAL(x)<1e10 && GSL_IMAG(x)<1e10){
			xprev=x;
			x = gsl_complex_mul_real(gsl_complex_add(xprev,gsl_complex_inverse(xprev)),0.5);
			iter++;
		}
		gi[m1][m2]=(unsigned char) iter % GLEVELS;
		iter = 0;
	}
}

void n3(int t){
	int iter;
	double linesd = (double) lines;
	int m1, m2;
	double xc, yc;
	gsl_complex x, xprev;
	for(size_t flati=0; flati < lines*(lines/nthreads); ++flati){
		m2 = flati % lines;
		m1 = t+(flati/lines)*nthreads;
		xc = -2+4*m2/linesd+4/(2*linesd);
		yc = -2+4*(linesd-1-m1)/linesd+4/(2*linesd);
		xprev = gsl_complex_rect(xc,yc);
		x = gsl_complex_add(gsl_complex_mul_real(xprev,0.6666666666666666),gsl_complex_mul_real(gsl_complex_inverse(X2),0.3333333333333333));
		while(notisclose3(x) && gsl_complex_abs2(x)>=1e-6 && GSL_REAL(x)<1e10 && GSL_IMAG(x)<1e10){
			xprev=x;
			x = gsl_complex_add(gsl_complex_mul_real(xprev,0.6666666666666666),gsl_complex_mul_real(gsl_complex_inverse(X2),0.3333333333333333));
			iter++;
		}
		gi[m1][m2]= (unsigned char) (iter*10) % GLEVELS;
		iter = 0;
	}
}

void n4(int t){
}

void n5(int t){
	int iter;
	double linesd = (double) lines;
	int m1, m2;
	double xc, yc;
	gsl_complex x, xprev;
	for(size_t flati=0; flati < lines*(lines/nthreads); ++flati){
		m2 = flati % lines;
		m1 = t+(flati/lines)*nthreads;
		xc = -2+4*m2/linesd+4/(2*linesd);
		yc = -2+4*(linesd-1-m1)/linesd+4/(2*linesd);
		xprev = gsl_complex_rect(xc,yc);
		x = gsl_complex_add(gsl_complex_mul_real(xprev,0.8),gsl_complex_mul_real(gsl_complex_inverse(X4),0.2));
		while(notisclose5(x) && gsl_complex_abs2(x)>=1e-6 && GSL_REAL(x)<1e10 && GSL_IMAG(x)<1e10){
			xprev=x;
			x = gsl_complex_add(gsl_complex_mul_real(xprev,0.8),gsl_complex_mul_real(gsl_complex_inverse(X4),0.2));
			iter++;
		}
		gi[m1][m2]= (unsigned char) iter % GLEVELS;
		iter = 0;
	}
}

void n6(int t){
}

void n7(int t){
	int iter;
	double linesd = (double) lines;
	int m1, m2;
	double xc, yc;
	gsl_complex x, xprev;
	//with lines*lines/nthreads we get overflow
	//lines*(lines/nthreads) works though
	for(size_t flati=0; flati < lines*(lines/nthreads); ++flati){
		m2 = flati % lines;
		m1 = t+(flati/lines)*nthreads;	
		xc = -2+4*m2/linesd+4/(2*linesd);
		yc = -2+4*(linesd-1-m1)/linesd+4/(2*linesd);
		xprev = gsl_complex_rect(xc,yc);
		x = gsl_complex_add(gsl_complex_mul_real(xprev,0.8571428571428571),gsl_complex_mul_real(gsl_complex_inverse(X6),0.14285714285714285));
		while(notisclose7(x) && gsl_complex_abs2(x)>=1e-6 && GSL_REAL(x)<1e10 && GSL_IMAG(x)<1e10){
			xprev=x; //not using xprev anymore, optimize it away
			x = gsl_complex_add(gsl_complex_mul_real(xprev,0.8571428571428571),gsl_complex_mul_real(gsl_complex_inverse(X6),0.14285714285714285));
			iter++;
		}	
		gi[m1][m2]=(unsigned char) (iter*10) % GLEVELS;
		iter = 0;
	}
}

void nbig(int t){
}

void *newton(void *arg){
	int t = (int) arg; 
	//Had a nasty bug here once, it said "int t = (int) t;" but somehow gcc
	//didn't catch it. It caused only every tth row to be written to file.
	if (d == 1){
		n1(t);
	}else if(d == 2){
		n2(t);
	}else if(d == 3){
		n3(t);
	}else if(d == 4){
		n4(t);
	}else if(d == 5){
		n5(t);
	}else if(d == 6){
		n6(t);
	}else if(d == 7){
		n7(t);
	}else{
		//With gsl and a fast pow
		nbig(t);
	}	
	return NULL;
}

int main(int argc, char *argv[]){
	//third roots of unity
	z3_0 = gsl_complex_rect(1,0);
	z3_1 = gsl_complex_rect(-0.5,0.8660254037844386);
	z3_2 = gsl_complex_rect(-0.5,-0.8660254037844386);

	//fifth roots of unity
	z5_0 = gsl_complex_rect(1,0);
	z5_1 = gsl_complex_rect(0.30901699437494745,0.9510565162951535);
	z5_2 = gsl_complex_rect(-0.8090169943749475,0.5877852522924731);
	z5_3 = gsl_complex_rect(-0.8090169943749475,-0.5877852522924731);
	z5_4 = gsl_complex_rect(0.30901699437494745,-0.9510565162951535);

	//seventh roots of unity
	z7_0 = gsl_complex_rect(1,0);
	z7_1 = gsl_complex_rect(0.6234898018587336,0.7818314824680298);
	z7_2 = gsl_complex_rect(-0.22252093395631445,0.9749279121818236);
	z7_3 = gsl_complex_rect(-0.9009688679024191,0.4338837391175581);
	z7_4 = gsl_complex_rect(-0.9009688679024191,-0.4338837391175581);
	z7_5 = gsl_complex_rect(-0.22252093395631445,-0.9749279121818236);
	z7_6 = gsl_complex_rect(0.6234898018587336,-0.7818314824680298);

	nthreads = (int)strtol(argv[1]+2,NULL,10);
	lines = (int)strtol(argv[2]+2,NULL,10);
	d = (int)strtol(argv[3],NULL,10);
	printf("nthreads = %d, lines = %d, d = %d\n",nthreads,lines,d);
	
	//Initializing the images
	gi = (unsigned char **)malloc(sizeof(char*)*lines);
	gi_entries = (unsigned char *)malloc(sizeof(char)*lines*lines);
	ci = (int **)malloc(sizeof(int *)*lines);
	ci_entries = (int *)malloc(sizeof(int)*lines*lines);
	for(size_t i=0, j=0; i < lines; ++i, j+=lines){
		gi[i]=gi_entries+j;
		ci[i]=ci_entries+j;
	}
	for(size_t i=0; i < lines*lines; ++i){
		gi_entries[i]=(unsigned char)0;
		ci_entries[i]=0;
	}

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
		if(ret = pthread_create(threads+t, NULL, newton, (void*)t)){
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
	//Write to file
	FILE * file;
	file=fopen("grayscale.pgm","wb");
	fprintf(file,"P5\n%d %d\n%d\n",lines,lines,GLEVELS);
	fwrite(gi_entries,sizeof(unsigned char),lines*lines,file);
	fclose(file);
	free(gi_entries);
	free(gi);	
	timespec_get(&stop, TIME_UTC);
	elapsed = (stop.tv_sec+1e-9*stop.tv_nsec)-(start.tv_sec+1.0e-9*start.tv_nsec);
	printf("elapsed incl wr=%.15Lf secs\n",elapsed);
	return 0;
}
