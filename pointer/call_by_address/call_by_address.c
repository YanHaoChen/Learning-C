#include <stdlib.h>
#include <stdio.h>

void sum(int *result, int *a, int *b){
	*result = *a + *b;
}

int main(){
	int a=10;
	int b=20;
	int result = 0;
	sum(&result, &a, &b);
	printf("result:%d",result);
	return 0;
}
