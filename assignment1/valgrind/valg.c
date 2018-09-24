#include <stdio.h>
#include <stdlib.h>

#define N 1000000000

void allocateints(){
	int * l = (int *)malloc(sizeof(int)*1000);
}

int main(){
	allocateints();
	long sum = 0;
	for(size_t i=0; i < N; ++i)
		sum+=i;
	printf("sum = %ld\n",sum);
	return 0;
}
