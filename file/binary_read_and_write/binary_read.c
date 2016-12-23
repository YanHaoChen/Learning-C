#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct student {
	char std_id[20];
	char name[20];
};

FILE *file_print;

int main(){
	struct student std[10];

	if((file_print=fopen("student_info","rb"))==NULL){
		printf("error");
		exit(1);
	}
	int size_of_file; 
	fseek(file_print,0,SEEK_END);
	size_of_file = (int)ftell(file_print);
	fseek(file_print,0,SEEK_SET);	

	int size_of_struct;
	size_of_struct = (int)sizeof(struct student);
	int num_of_data;
	num_of_data = size_of_file / size_of_struct;	
	int num;
	num = fread(std,sizeof(struct student),num_of_data,file_print);
	
	int i;
	for(i=0;i<num;i++){
		printf("std_id:%s ,name:%s\n",std[i].std_id,std[i].name);
	}	


	fclose(file_print);
	return 0;
}
