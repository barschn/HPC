#include <stdio.h>
#include <stdlib.h>

int main(){
	FILE *file;
	int ** mat =(int**) malloc(sizeof(int*)*10);
	int * matentries=(int*)malloc(sizeof(int)*100);
	for(size_t ix=0,jx=0; ix<10; ++ix,jx+=10)
		mat[ix]=matentries+jx;
	for(size_t ix=0; ix < 100; ++ix)
		matentries[ix]=11;
	file=fopen("ints.bin","wb");
	fwrite(matentries,sizeof(int),100*sizeof(int),file);
	fclose(file);
	return 0;
}
