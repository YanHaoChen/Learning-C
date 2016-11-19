#include <stdio.h>
#include <stdlib.h>

#define MAX_COUNT 20

int create_subset(int[],int[],int,int);

int main(){
    int num_count = 0;
    
    printf("How much number do you want create in a set? (<=20)");
    scanf("%d",&num_count);
    if (num_count > MAX_COUNT){
        printf("Too much!!");
        return 0;
    }
    int set_array[20];
    int bool_array[20];
    for(int i=0; i<num_count ; i++){
        scanf("%d",&set_array[i]);
        bool_array[i]=0;
    }
    
    printf("All sets => {}");
    create_subset(set_array,bool_array,0,num_count);
    return 0;
}

int create_subset(int set_array[],int bool_array[],int count,int all_num){
    int next_bool[20];
    for(int i = 0; i<all_num;i++){
        next_bool[i] = bool_array[i];
    }
    if(count < all_num){
        
        next_bool[count]=1;
        printf("{");
        for(int i = 0; i<all_num;i++){
            if(next_bool[i]){
                printf(" %d ",set_array[i]);
            }
        }
        printf("}");
        create_subset(set_array,bool_array,count+1,all_num);
        create_subset(set_array,next_bool ,count+1,all_num);
    }
    return 0;
}
