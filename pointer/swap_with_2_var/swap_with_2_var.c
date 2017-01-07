#include <stdlib.h>
#include <stdio.h>


void swap(int *a,int *b){
	*(b+2)= *a;
	*a = *b;
	*b = *(b+2);
}

int main(){
	int *a,*b;
	a = (int*)malloc(sizeof(int));
	b = (int*)malloc(sizeof(int));
	*a = 10;
	*b = 20;

	swap(a,b);
	printf("a:%d,b:%d",*a,*b);
	
return 0;
}
