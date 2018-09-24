#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1048576


void main(){
	struct timespec start, stop;
	long double elapsed;
	int * l = (int*) malloc(sizeof(int)*SIZE);
	for( size_t i = 0; i < SIZE; ++i){
		l[i]=i;
	}
	FILE * file, * files;

	//Writing
	file=fopen("ints.bin","wb");
	files=fopen("/run/mount/scratch/tobias/ints.bin","wb");
	
	//HDD
	//TIME START, HDD
	timespec_get(&start,TIME_UTC);
	fwrite(l,sizeof(int),SIZE,file);
	fflush(file);
	timespec_get(&stop,TIME_UTC);
	//TIME END, HDD
	elapsed = (stop.tv_sec + 1.0e-9*stop.tv_nsec) - (start.tv_sec + 1.0e-9*start.tv_nsec);
	printf("hdd w: %Lf10 secs.\n",elapsed);
	
	//SSD
	//TIME START, SSD
	timespec_get(&start,TIME_UTC);
	fwrite(l,sizeof(int),SIZE,files);
	fflush(files);
	timespec_get(&stop,TIME_UTC);
	//TIME END, SSD
	elapsed = (stop.tv_sec + 1.0e-9*stop.tv_nsec) - (start.tv_sec + 1.0e-9*start.tv_nsec);
	printf("ssd w: %Lf10 secs.\n",elapsed);
	
	
	fclose(file);
	fclose(files);

	//Reading
	file=fopen("ints.bin","rb");
	files=fopen("/run/mount/scratch/tobias/ints.bin","rb");
	
	//HDD
	//TIME START, HDD
	timespec_get(&start,TIME_UTC);
	fread(l,sizeof(int),SIZE,file);
	timespec_get(&stop,TIME_UTC);
	//TIME END, HDD
	elapsed = (stop.tv_sec + 1.0e-9*stop.tv_nsec) - (start.tv_sec + 1.0e-9*start.tv_nsec);
	printf("hdd r: %Lf10 secs.\n",elapsed);
	
	//SSD
	//TIME START, SSD
	timespec_get(&start,TIME_UTC);
	fread(l,sizeof(int),SIZE,files);
	timespec_get(&stop,TIME_UTC);
	//TIME END, SSD
	elapsed = (stop.tv_sec + 1.0e-9*stop.tv_nsec) - (start.tv_sec + 1.0e-9*start.tv_nsec);
	printf("ssd r: %Lf10 secs.\n",elapsed);
	
	fclose(file);
	fclose(files);
	free(l);
	exit(0);
}
