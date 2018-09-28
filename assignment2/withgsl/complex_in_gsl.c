#include <stdio.h>
#include <gsl/gsl_complex.h>
#include <gsl/gsl_complex_math.h>

int main(){
	gsl_complex z = gsl_complex_rect(1.0,1.0);
	gsl_complex zpow [4] = {gsl_complex_pow_real(z,1),
				gsl_complex_pow_real(z,2),
				gsl_complex_pow_real(z,3),
				gsl_complex_pow_real(z,4)};
	for(size_t i=0; i < 4; ++i)
		printf("%lf + I*%lf\n",GSL_REAL(*(zpow+i)),GSL_IMAG(*(zpow+i)));
	return 0;
}
