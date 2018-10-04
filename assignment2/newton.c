//Highlight every occurence of a word, write *

#include <pthread.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <gsl/gsl_complex.h>
#include <gsl/gsl_complex_math.h>
#include <gsl/gsl_math.h>

#define GLEVELS 255
#define CLEVELS 255
#define WAITTIME 50000

//NOTE THAT THESE DO NOT USE xprev ANYMORE!

#define X2 gsl_complex_rect(GSL_REAL(x)*GSL_REAL(x)-GSL_IMAG(x)*GSL_IMAG(x),2*GSL_REAL(x)*GSL_IMAG(x))

#define X4 gsl_complex_rect(GSL_REAL(x)*GSL_REAL(x)*GSL_REAL(x)*GSL_REAL(x)-6*GSL_REAL(x)*GSL_REAL(x)*GSL_IMAG(x)*GSL_IMAG(x)+GSL_IMAG(x)*GSL_IMAG(x)*GSL_IMAG(x)*GSL_IMAG(x),4*(GSL_REAL(x)*GSL_REAL(x)*GSL_REAL(x)*GSL_IMAG(x)-GSL_REAL(x)*GSL_IMAG(x)*GSL_IMAG(x)*GSL_IMAG(x)))

#define X6 gsl_complex_rect(-1.0*GSL_IMAG(x)*GSL_IMAG(x)*GSL_IMAG(x)*GSL_IMAG(x)*GSL_IMAG(x)*GSL_IMAG(x)+15.0*GSL_IMAG(x)*GSL_IMAG(x)*GSL_IMAG(x)*GSL_IMAG(x)*GSL_REAL(x)*GSL_REAL(x)-15.0*GSL_IMAG(x)*GSL_IMAG(x)*GSL_REAL(x)*GSL_REAL(x)*GSL_REAL(x)*GSL_REAL(x)+GSL_REAL(x)*GSL_REAL(x)*GSL_REAL(x)*GSL_REAL(x)*GSL_REAL(x)*GSL_REAL(x),6.0*GSL_IMAG(x)*GSL_IMAG(x)*GSL_IMAG(x)*GSL_IMAG(x)*GSL_IMAG(x)*GSL_REAL(x)-20.0*GSL_IMAG(x)*GSL_IMAG(x)*GSL_IMAG(x)*GSL_REAL(x)*GSL_REAL(x)*GSL_REAL(x)+6.0*GSL_IMAG(x)*GSL_REAL(x)*GSL_REAL(x)*GSL_REAL(x)*GSL_REAL(x)*GSL_REAL(x))

FILE * gfile,* cfile;
int nthreads;
int lines;
int d;


const struct timespec sleep_timespec = {.tv_sec = 0, .tv_nsec=WAITTIME};

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

pthread_mutex_t mutex_item_done;

//As for the datatype of the images, we simply use lists of strings
//Why? Because it's easiest to write, and consumes relatively little space
char ** gi; //Gray image
char * gi_entries;

char ** ci; //RGB image
char * ci_entries;

char * item_done; //For the rows, Martin's nomenclature

//Note the trailing whitespace
//We use this for reasons of beautifying the output
char * colors[]={
	"  0   0   0 ",
	"  0   0 255 ",
	"  0 255   0 ",
	"  0 255 255 ",
	"255   0   0 ",
	"255   0 255 ",
	"255 255   0 ",
	"255 255 255 "
};

/*
//FIXME
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

//FIXME
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

//FIXME
int notisclose4(gsl_complex x){
	return 1;
}
*/
int isclose5(gsl_complex x){
	if((abs(GSL_REAL(x)-GSL_REAL(z5_0)) >= 1e-3 || abs(GSL_IMAG(x)-GSL_IMAG(z5_0)) >= 1e-3)
			&& (abs(GSL_REAL(x)-GSL_REAL(z5_1)) >= 1e-3 || abs(GSL_IMAG(x)-GSL_IMAG(z5_1)) >= 1e-3)
			&& (abs(GSL_REAL(x)-GSL_REAL(z5_2)) >= 1e-3 || abs(GSL_IMAG(x)-GSL_IMAG(z5_2)) >= 1e-3)
			&& (abs(GSL_REAL(x)-GSL_REAL(z5_3)) >= 1e-3 || abs(GSL_IMAG(x)-GSL_IMAG(z5_3)) >= 1e-3)
			&& (abs(GSL_REAL(x)-GSL_REAL(z5_4)) >= 1e-3 || abs(GSL_IMAG(x)-GSL_IMAG(z5_4)) >= 1e-3)){
		return 0;
	}else if(gsl_complex_abs2(gsl_complex_sub(x,z5_0))>=1e-6
			&& gsl_complex_abs2(gsl_complex_sub(x,z5_1))>=1e-6
			&& gsl_complex_abs2(gsl_complex_sub(x,z5_2))>=1e-6
			&& gsl_complex_abs2(gsl_complex_sub(x,z5_3))>=1e-6
			&& gsl_complex_abs2(gsl_complex_sub(x,z5_4))>=1e-6){
		return 0;
	}else if (gsl_complex_abs2(gsl_complex_sub(x,z5_0))<1e-6){
		return 1;
	}else if (gsl_complex_abs2(gsl_complex_sub(x,z5_1))<1e-6){
		return 2;
	}else if (gsl_complex_abs2(gsl_complex_sub(x,z5_2))<1e-6){
		return 3;
	}else if (gsl_complex_abs2(gsl_complex_sub(x,z5_3))<1e-6){
		return 4;
	}else{
		return 5;
	}

}
/*
//FIXME
int notisclose6(gsl_complex x){
	return 1;
}

//FIXME
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

//FIXME
int notisclosebig(gsl_complex x){
	return 1;
}

void n1(int t){
	//FIXME, need to put in zeroes everywhere!
}

//FIXME
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

//FIXME
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

//FIXME
void n4(int t){
}
*/
//CURRENTLY FIXING THIS
void n5(int t){
	int iter;
	double linesd = (double) lines;
	int m1, m2;
	double xc, yc;
	int c = 0;
	gsl_complex x;
	char buffer[13];
	for(m1 = t; m1 < lines; m1+=nthreads){
		//Explanation of size: Each char is a byte, every color is on the form
		//	255 255 255 
		//which is, if we end on whitespace equal to 12 chars, i. e. 12 bytes.
		//For this to be formatted correctly on output we also need the newline
		//char (but _NOT_ the null character)
		char * grow = (char *)malloc(12*lines+1);
		char * crow = (char *)malloc(12*lines+1);
		for(m2 = 0; m2 < lines; ++m2){
			xc = -2+4*m2/linesd+4/(2*linesd);
			yc = -2+4*(linesd-1-m1)/linesd+4/(2*linesd);
			x=gsl_complex_rect(xc,yc);
			while((c=isclose5(x))==0 && gsl_complex_abs2(x)>=1e-6 && GSL_REAL(x)<1e10 && GSL_IMAG(x)<1e10){
				x = gsl_complex_add(gsl_complex_mul_real(x,0.8),gsl_complex_mul_real(gsl_complex_inverse(X4),0.2));
				iter++;
			}
			//DEBUG printf("iter = %d\n(iter*10) mod GLEVELS = %d\n",iter,(iter*10)%GLEVELS);
			sprintf(buffer,"%3d %3d %3d ",(iter*10)%GLEVELS,(iter*10)%GLEVELS,(iter*10)%GLEVELS);
			/*DEBUG printf("buffer =   {%c,%c,%c,%c,%c,%c,%c,%c,%c,%c,%c,%c,%c}\n",buffer[0],buffer[1],buffer[2],buffer[3],
										buffer[4],buffer[5],buffer[6],buffer[7],
										buffer[8],buffer[9],buffer[10],buffer[11],
										buffer[12]);*/
			/*DEBUG printf("colors+%d = {%c,%c,%c,%c,%c,%c,%c,%c,%c,%c,%c,%c,%c}\n",c,*(*(colors+c)+0),*(*(colors+c)+1),*(*(colors+c)+2),*(*(colors+c)+3),
											*(*(colors+c)+4),*(*(colors+c)+5),*(*(colors+c)+6),*(*(colors+c)+7),
											*(*(colors+c)+8),*(*(colors+c)+9),*(*(colors+c)+10),*(*(colors+c)+11),
							       				*(*(colors+c)+12));*/
			//memcpy'ing the color buffer to the strings grow and crow
			//Note that we skip the null character
			memcpy(grow+12*m2,buffer,12);
			memcpy(crow+12*m2,*(colors+c),12);
			//DEBUG printf("at m2 = %d and grow=%s\n",m2,grow);
			//DEBUG printf("at m2 = %d and crow=%s\n",m2,crow);
			iter = 0;
		}
		//Concatening a line break to the row we're at
			//Was
			//strcat(grow,"\n");
			//strcat(crow,"\n");
			//but this creates a lot of null characters ^@, and that's not nice
		sprintf(buffer,"\n");
		memcpy(grow+12*lines,buffer,1);
		memcpy(crow+12*lines,buffer,1);
		//DEBUG printf("grow = %s",grow);
		//DEBUG printf("crow = %s",crow);
		gi[m1]=grow;
		ci[m1]=crow;
		//Stealing this directly from Martin's lecture
		pthread_mutex_lock(&mutex_item_done);
		item_done[m1]=1;
		pthread_mutex_unlock(&mutex_item_done);
	}	
}
/*
//FIXME
void n6(int t){
}

//FIXME
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

//FIXME
void nbig(int t){
}
*/
void *write(void *arg){
	//Verbatim from Martin
	gfile=fopen("grayfile.ppm","w");
	cfile=fopen("colorfile.ppm","w");
	fprintf(gfile,"P3\n%d %d\n%d\n",lines,lines,GLEVELS);
	fprintf(cfile,"P3\n%d %d\n%d\n",lines,lines,GLEVELS);
	char *gresult, *cresult;
	char *item_done_loc = (char*)calloc(lines,sizeof(char));
	for(size_t ix=0; ix<lines; ){
		pthread_mutex_lock(&mutex_item_done);
		if(item_done[ix] != 0)
			memcpy(item_done_loc,item_done,lines*sizeof(char));
		pthread_mutex_unlock(&mutex_item_done);

		if(item_done_loc[ix] == 0){
			nanosleep(&sleep_timespec, NULL);
			continue;
		}

		for( ; ix < lines && item_done_loc[ix] != 0; ++ix){
			gresult=gi[ix];
			cresult=ci[ix];
			fwrite(gresult,lines*12+1,1,gfile);
			fwrite(cresult,lines*12+1,1,cfile);
			free(gresult);
			free(cresult);
		}
	}
	fclose(gfile);
	fclose(cfile);
}

void *newton(void *arg){
	int t = (int) arg; 
	//Had a nasty bug here once, it said "int t = (int) t;" but somehow gcc
	//didn't catch it. It caused only every tth row to be written to file.
	if (d == 1){
		//n1(t);
	}else if(d == 2){
		//n2(t);
	}else if(d == 3){
		//n3(t);
	}else if(d == 4){
		//n4(t);
	}else if(d == 5){
		n5(t);
	}else if(d == 6){
		//n6(t);
	}else if(d == 7){
		//n7(t);
	}else{
		//With gsl and a fast pow
		//nbig(t);
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

	//Initializing the item_done list
	item_done = (char*)malloc(sizeof(char)*lines);

	//Initializing the images
	//Note that we allocate non-contiguously
	gi = (char **)malloc(sizeof(char*)*lines);
	ci = (char **)malloc(sizeof(char*)*lines);	
	
	int ret;
	pthread_t threads[nthreads+1]; //with the write thread
	size_t t;

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
	pthread_mutex_init(&mutex_item_done,NULL);
	//Creation of newton threads
	for(t = 0; t < nthreads; ++t){
		if(ret = pthread_create(threads+t, NULL, newton, (void*)t)){
			printf("Error creating thread: %d\n", ret);
			exit(1);
		}
	}
	//Creation of write thread
	if(ret = pthread_create(threads+nthreads, NULL, write, NULL)){
		printf("Error creating thread: %d\n", ret);
		exit(1);
	}
	//Joining
	for(t = 0; t < nthreads+1; ++t){
		if(ret = pthread_join(threads[t], NULL)){
			printf("Error joining thread: %d\n", ret);
			exit(1);
		}
	}
	pthread_mutex_destroy(&mutex_item_done);		
	//Not writing here anymore
	//Look at the write-thread		
	timespec_get(&stop, TIME_UTC);
	elapsed = (stop.tv_sec+1e-9*stop.tv_nsec)-(start.tv_sec+1.0e-9*start.tv_nsec);
	printf("elapsed incl wr=%.15Lf secs\n",elapsed);
	return 0;
}
