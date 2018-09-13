#include <stdio.h>

void main(){
	for(size_t ix=0; ix < 10; ++ix)
		printf("%d\n",ix);
	printf("ix++\n");
	for(size_t ix=0; ix < 10; ix++)
		printf("%d\n",ix);
}
