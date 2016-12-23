#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student{
	char std_id[20];
	char name[20];
};

FILE *file_print;

int main(){
	struct student std[2];
	
	strncpy(std[0].std_id,"123",19);
	strcat(std[0].std_id,"\0");
	strncpy(std[0].name,"John",19);
	strcat(std[0].name,"\0");	
	
	strncpy(std[1].std_id,"678",19);
	strcat(std[1].std_id,"\0");
	strncpy(std[1].name,"Tom",19);
	strcat(std[1].name,"\0");	
	
	if((file_print=fopen("student_info","wb"))==NULL){
		printf("error");
		exit(1);
	}

	int num=0;

	num = fwrite(std,sizeof(struct student),2,file_print);
	printf("wrote:%d",num);
	fclose(file_print);
	return 0;
}
