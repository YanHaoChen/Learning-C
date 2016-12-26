#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student{
	char std_id[20];
	char name[20];
};

FILE *file_print;

int main(){

	if((file_print=fopen("student_info","r+b"))==NULL) {
		printf("error");
		exit(1);
	}
	int size_of_data;
	fseek(file_print,0,SEEK_END);
	size_of_data = (int)ftell(file_print);
	fseek(file_print,0,SEEK_SET);
	
	int num_of_data;
	num_of_data = size_of_data / (int)sizeof(struct student);
	printf("num_of_date:%d \n",num_of_data);
	int i;
	for(i=0;i < num_of_data; i++){
		struct student now_std[1];
		char new_name[20];
		fread(now_std, sizeof(struct student), 1, file_print);
		printf("now_std:%s\n",now_std[0].std_id);
		if(strcmp(now_std[0].std_id,"678")==0){
			size_t goto_position;
			goto_position = sizeof(struct student)*i;
			printf("goto:%lu \n",goto_position);
			fseek(file_print,goto_position,SEEK_SET);
			strncpy(now_std[0].name,"Bill",19);
			strcat(now_std[0].name,"\0");
			fwrite(now_std,sizeof(struct student),1,file_print);
			break;
		}
	}
	fclose(file_print);


	return 1;
}
