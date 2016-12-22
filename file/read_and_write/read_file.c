#include <stdio.h>
#include <stdlib.h>

FILE *file_print;

int main(){
	// with fgetc
	char get_char;
	file_print = fopen("./test.txt","r");
	
	if(file_print == NULL){
		printf("error");
		exit(1);
	}
	while((get_char=fgetc(file_print)) != EOF){
		printf("%c",get_char);
	}
	fclose(file_print);
	
	//with fgets
	char get_str[20];
	file_print = fopen("./test.txt","r");
	
	if(file_print == NULL){
		printf("error");
		exit(1);
	}
	printf("\n");	
	while(fgets(get_str,20,file_print) != NULL){
		printf("%s",get_str);
	}
	fclose(file_print);	
	
	//with fscanf
	char get_str2[20];
	file_print = fopen("./test.txt","r");
	
	if(file_print == NULL){
		printf("error");
		exit(1);
	}
	printf("\n");	
	while(fscanf(file_print,"%s",get_str2) != EOF){
		printf("%s ",get_str2);
	}
	fclose(file_print);	
	
	return 0;
}
