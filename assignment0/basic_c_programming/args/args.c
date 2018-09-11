#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void main(int argc, char *argv[]){
	char cmp[] = "-a";
	int ais = 0;
	int bis = 0;
	if (strcmp(argv[1],cmp) == 0){
		ais=strtol(argv[2],NULL,10);
		bis=strtol(argv[4],NULL,10);
	} else {
		ais=strtol(argv[4],NULL,10);
		bis=strtol(argv[2],NULL,10);
	}
	printf("A is %d and B is %d\n",ais,bis);
}
