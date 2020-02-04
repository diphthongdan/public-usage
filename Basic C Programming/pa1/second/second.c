#include <stdlib.h>
#include <stdio.h>

typedef struct nodes {
	int data;
	struct nodes* next;
} node;
node* front=NULL;
int size;
void insertNode(int);
void deleteNode(int);
void deleteList();

int main(int argc, char** argv){
	int temp;
	char command;
	FILE* fp;
	fp=fopen(argv[1],"r");
	if(fp==NULL){
	printf("error\n");
	return 0;
	}
	if(fscanf(fp,"%c\t%d\n",&command,&temp)==EOF){
		printf("0\n\n");
		return 0;
	}
	size=0;
	if(command=='i'){
	front=malloc(sizeof(node));
	front->data=temp;
	front->next=NULL;
	size++;
	}
	while(fscanf(fp,"%c\t%d\n",&command,&temp)!=EOF){
		if(command=='i'){
		insertNode(temp);
		}
		if(command=='d'){
		deleteNode(temp);
		}
	}
	node* ptr=front;
	printf("%d\n",size);
	while(ptr!=NULL){
	printf("%d\t",ptr->data);
	ptr=ptr->next;
	}
	fclose(fp);
	deleteList();
	return 0;
}

void insertNode(int num){
	node* temp=malloc(sizeof(node));
	temp->data=num;
	temp->next=NULL;
	if(front==NULL){
		front=temp;
		size++;
		return;
	}
	if(front->next==NULL){
		if(front->data<temp->data){
			front->next=temp;
			size++;
			return;
		}
		if(front->data==temp->data){
			free(temp);
			return;
		}
		if(front->data>temp->data){
			temp->next=front;
			front=temp;
			size++;
			return;
		}
	}
	node* ptr=front;
	while(ptr!=NULL){
		if(ptr->data==temp->data){
			free(temp);
			return;
		}
		if(ptr->data<temp->data){
			if(ptr->next==NULL){
			ptr->next=temp;
			size++;
			return;
			}
			if(ptr->next->data>temp->data){
			temp->next=ptr->next;
			ptr->next=temp;
			size++;
			return;
			}
		}
		if(ptr->data>temp->data){
			if(ptr->data==front->data){
			temp->next=ptr;
			front=temp;
			size++;
			return;
			}
		}
		ptr=ptr->next;
	}
	
	return;
	
}
void deleteNode(int num){
	if(front->data==num){
	front=front->next;
	size--;
	return;	
	}
	node* ptr=front;
	node* prev=NULL;
	while(ptr!=NULL){
		if(ptr->data==num){
		prev->next=ptr->next;
		size--;
		return;
		}
	prev=ptr;
	ptr=ptr->next;
	}
	return;
}
void deleteList(){
	node* temp=front;
	node* temp2;
	while(temp!=NULL){
	temp2=temp;
	temp=temp->next;
	free(temp2);	
	}
}
