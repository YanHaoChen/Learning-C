#include <stdlib.h>
#include <stdio.h>

struct Node {
	int data;
	struct Node *link;
};

typedef struct Node node;
typedef node *nodePointer;

nodePointer GetNode();
nodePointer InitList(int first_data);
nodePointer InsertNode(nodePointer now_list, int insert_num);
int main(){
	nodePointer num_list;
	num_list = InitList(1);
	num_list = InsertNode(num_list, 2);	
	num_list = InsertNode(num_list, 3);	
	num_list = InsertNode(num_list, 4);	
	num_list = InsertNode(num_list, 5);	
	num_list = InsertNode(num_list, 6);	
	num_list = InsertNode(num_list, 7);	
	num_list = InsertNode(num_list, 8);

	while(num_list->link != NULL){
		printf("num:%d\n", num_list->data);
		num_list = num_list->link;
	}
	
	return 0;
}

nodePointer GetNode(){
	nodePointer new_node;
	new_node = (nodePointer)malloc(sizeof(node));
	if(new_node == NULL){
		printf("Get a new node has failed.");
	}
	return new_node;
}

nodePointer InitList(int first_data){
	nodePointer header_node;
	header_node = GetNode();
	header_node->data = first_data;
	header_node->link = NULL;
	return header_node;	
}

nodePointer InsertNode(nodePointer now_list, int insert_num) {
	nodePointer temp_node;
	temp_node = now_list;
	while (temp_node->link != NULL){
		temp_node = temp_node->link; 		
	}
	if(temp_node != NULL){
		nodePointer insert_node;
		insert_node = GetNode();
		insert_node->data = insert_num;
		insert_node->link = NULL;
		temp_node->link = insert_node;
	} else {
		printf("Insert a node has failed");
	}
	return now_list;	
}
