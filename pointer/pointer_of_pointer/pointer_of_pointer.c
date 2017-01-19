#include <stdlib.h>
#include <stdio.h>

int main(){
	int *pointer;
	int **pointer_of_pointer;
	
	/* pointer malloc */
	printf("/ pointer /\n\n");
	pointer = (int*)malloc(sizeof(int));
	*pointer = 0;
	printf("value:%d\n",*pointer);

	/* pointer malloc [3] */
	printf("\n/ pointer [3] /\n\n");
	pointer = (int*)malloc(sizeof(int)*3);
	int z;
	for(z=0;z<3;z++){
		*(pointer+z) = z;
		printf("array[%d], value:%d\n",z,*(pointer+z));
	}
	
	/* pointer_of_pointer malloc [2][3] */
	printf("\n/ pointer_of_pointer [2][3] /\n\n");
	int i,j;
	pointer_of_pointer = (int*)malloc(sizeof(int)*2);
	for(i=0;i<2;i++){
		*(pointer_of_pointer+i) = (int*)malloc(sizeof(int)*3);
	}
	for(i=0;i<2;i++){
		for(j=0;j<3;j++){
			*(*(pointer_of_pointer+i)+j) = j+i;
			printf("array[%d][%d], value:%d\n",i,j,*(*(pointer_of_pointer+i)+j));
		}
	}
}
