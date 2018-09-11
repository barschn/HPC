#include <stdio.h>
#include <stdlib.h>

void mul_cpx_mainfile(double * a_re, double * a_im, double * b_re, double * b_im, double * c_re, double * c_im){
	*a_re = (*b_re)*(*c_re)-(*b_im)*(*c_im);
	*a_im = (*b_re)*(*c_im)+(*b_im)*(*c_re);
}

void main(){
	printf("Test: Input Re(b), Im(b), Re(c), Im(c), in that order.\n");
	double * A_re, * A_im,* B_re, * B_im, * C_re, * C_im;
	A_re=malloc(sizeof(double));
	A_im=malloc(sizeof(double));
	B_re=malloc(sizeof(double));
	B_im=malloc(sizeof(double));
	C_re=malloc(sizeof(double));
	C_im=malloc(sizeof(double));
	scanf("%lf",B_re);
	scanf("%lf",B_im);
	scanf("%lf",C_re);
	scanf("%lf",C_im);
	mul_cpx_mainfile(A_re,A_im,B_re,B_im,C_re,C_im);
	printf("Result: %lf + %lf*I\n",*A_re,*A_im);
}
