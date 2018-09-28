#include <stdio.h>
#include <stdlib.h>
#include <tgmath.h>
#include <complex.h>

int d;

void newtoniter(double complex * in){
	printf("newtoniter start\n");
	double complex xprev = *in;
	*in=xprev-(pow(xprev,d)-1)/(d*pow(xprev,d-1));
	int iter=0;
	while(cabs(*in-xprev)>=1e-3){
		printf("newtoniter loop %d\n",iter++);
		xprev=*in;
		*in=xprev-(pow(xprev,d)-1)/(d*pow(xprev,d-1));
	}
}

int main(int argc, char * argv[]){
	d = (int) strtol(argv[1],NULL,10);
	while(1){
		double x0re, x0im;
		scanf("%lf",&x0re);
		scanf("%lf",&x0im);
		double complex *x0 = (double complex*)malloc(sizeof(double complex));
		*x0=x0re+I*x0im;
		newtoniter(x0);
		printf("%lf + I*%lf\n",creal(*x0),cimag(*x0));
	}
}


