#include <stdio.h>

struct rgb{
	int r;
	int g;
	int b;
};

const struct rgb colorarray[]={
		{.r = 0, .g = 0, .b = 0},
		{.r = 0, .g = 0, .b = 1}
	};

int main(){	
	//colorarray[1].r=(unsigned char)0;
	//colorarray[1].g=(unsigned char)0;
	//colorarray[1].b=(unsigned char)2;
	printf("%d %d %d\n",colorarray[1].r,colorarray[1].g,colorarray[1].b);
	return 0;
}
