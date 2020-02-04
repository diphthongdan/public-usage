#include<stdio.h>
#include<stdlib.h>
typedef struct nodes{
	int data;
	int height;
	struct nodes* left;
	struct nodes* right;	
} node;
node* root=NULL;
void insert(int);
void search(int);
void insert(int value){
	node* temp=malloc(sizeof(node));
	temp->left=NULL;
	temp->right=NULL;
	temp->data=value;
	if(root==NULL){
		temp->height=1;
		root=temp;
		printf("inserted %d\n",temp->height);
		return;
	}
	node* ptr=malloc(sizeof(node));
	ptr=root;
	int i=1;
	while(ptr!=NULL){
		if(value>ptr->data){
			if(ptr->right==NULL){
				temp->height=i+1;
				ptr->right=temp;
				printf("inserted %d\n",ptr->right->height);
				return;
			}
			ptr=ptr->right;
			i++;
			continue;
		}else if(value<ptr->data){
			if(ptr->left==NULL){
				temp->height=i+1;
				ptr->left=temp;
				printf("inserted %d\n",ptr->left->height);
				return;
			}
			ptr=ptr->left;
			i++;
			continue;
		}else if(value==ptr->data){
		printf("duplicate\n");
		return;
		}
	}
	return;
}
void search(int value){
	node* ptr=root;
	while(ptr!=NULL){
		if(ptr->data==value){
		printf("present %d\n",ptr->height);
		return;
		}
		if(ptr->data>value){
		ptr=ptr->left;
		} else if(ptr->data<value){
		ptr=ptr->right;
		}
	}
	printf("absent\n");
	return;
}
int main(int argc, char** argv){
	FILE* fp;
	fp=fopen(argv[1],"r");
	if(fp==NULL){
		printf("error");
		return 0;
	}
	int value;
	char command;
	while(fscanf(fp,"%c\t%d\t",&command,&value)!=EOF){
		if(command=='i'){
			insert(value);
		}
		if(command=='s'){
			search(value);
		}
	}
	
	return 0;
}
