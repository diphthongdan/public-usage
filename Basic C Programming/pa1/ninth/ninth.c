#include<stdio.h>
#include<stdlib.h>
typedef struct nodes{
	int data;
	int height;
	struct nodes* left;
	struct nodes* right;	
} node;
node* root=NULL;
void recursiveFree(node*);
void insert(int);
void search(int);
void delete(int);
void updateHeight(node*,int);
void recursiveFree(node* ptr){
	if(ptr==NULL){
		return;	
	}
	recursiveFree(ptr->right);
	recursiveFree(ptr->left);
	free(ptr);
	return;
}
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
void delete(int value){
	node* ptr=root;
	node* prev=NULL;
	while(ptr!=NULL){
		if(ptr->data==value){
			break;
			}
		if(ptr->data>value){
			prev=ptr;
			ptr=ptr->left;
			} else {
			prev=ptr;
			ptr=ptr->right;
			}
		}
	if(ptr==NULL){
	printf("fail\n");
	return;
	}
	node* replace=NULL;
	if(ptr->right!=NULL&&ptr->left!=NULL){
		replace=ptr->right;
		prev=ptr;
		while(replace->left!=NULL){
			prev=replace;
			replace=replace->left;
		}
		ptr->data=replace->data;
		ptr=replace;
	}
	node* tmp=NULL;
	if(ptr->right!=NULL){
		tmp=ptr->right;
	}else {
		tmp=ptr->left;
	}
	
if(prev!=NULL){
	if(ptr==prev->right){
		prev->right=tmp;
	} else {
		prev->left=tmp;
	}
} else {
	if(root->data==ptr->data){
	root=tmp;
	} else {
	ptr=tmp;
	}
	}
	printf("success\n");
	return;
	
}
void updateHeight(node* ptr,int height){
	if(ptr==NULL){
		return;
	}
	ptr->height=height;
	updateHeight(ptr->right,height+1);
	updateHeight(ptr->left,height+1);
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
		if(command=='d'){
			delete(value);
			updateHeight(root,1);
		}
	}
	recursiveFree(root);
	return 0;
}
