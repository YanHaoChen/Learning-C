#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define COMPARE(x,y) (((x) < (y))? 1: ((x) == (y)) ? 0 : -1)

int binsearch(int [],int, int, int);

int main(){
	int searchnum = 0;
	int list[10];
	int i;
	for(i=0;i<10;i++){
		list[i] = i+1;
		printf("%d ", list[i]);
	}
	printf("\n");
	
	printf("What the number you want to search? ");
	scanf("%d", &searchnum);
	int result = binsearch(list, searchnum, 0, 9);
	if (result > -1){
		printf("Get it at index of %d!", result);
	}else{
		printf("Not found.");
	}
	return -1;
}

int binsearch(int list[], int searchnum, int left, int right){
	int middle;
	while (right >= left){
		middle = (right+left) / 2;
		switch (COMPARE(searchnum,list[middle])){
			case 1: right = middle -1;
					break;
			case 0: return middle;
			case -1: left = middle +1;
					break;
		}
	}
return -1;	
}
