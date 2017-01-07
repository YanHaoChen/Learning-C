#include <stdlib.h>
#include <stdio.h>


void swap(int *a,int *b){
	b[1]= *a;
	*a = b[0];
	b[0] = b[1];
}

int main(){
	int *a,*b;
	a = (int*)malloc(sizeof(int));
	b = (int*)malloc(sizeof(int)*2);
	*a = 10;
	b[0] = 20;

	swap(a,&b[0]);
	printf("a:%d,b:%d",*a,b[0]);
	
return 0;
}

