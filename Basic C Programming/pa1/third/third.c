#include<stdlib.h>
#include<stdio.h>

typedef struct nodes{
	int data;
	int key;
	struct nodes* next;
} node;

int hash(int);
void search(int,node**);
void insert(int,node**);
void deleteTable(node**);
int hash(int data){
	data=abs(data);
	return data%1000;
}
void insert(int num,node** hashMap){
	int key=hash(num);
	node* temp=malloc(sizeof(node));
	temp->data=num;
	temp->next=NULL;
	if(hashMap[key]==NULL){
		hashMap[key]=temp;
		printf("inserted\n");
		return;
	} else{
	node* ptr=hashMap[key];
	while(ptr!=NULL){
		if(ptr->data==num){
			printf("duplicate\n");
			free(temp);
			return;		
			}
		ptr=ptr->next;
		}
	temp->next=hashMap[key];
	hashMap[key]=temp;
	printf("inserted\n");
	return;
	}
	return;
}
void search(int num,node** hashMap){
	int key=hash(num);
	if(hashMap[key]==NULL){
		printf("absent\n");
		return;
	}
	node* ptr=hashMap[key];
	while(ptr!=NULL){
		if(ptr->data==num){
		printf("present\n");
		return;
		}
		ptr=ptr->next;
	}
	printf("absent\n");
	return;
	
}
void deleteTable(node** hashMap){
	for(int i=0;i<1000;i++){
		if(hashMap[i]!=NULL){
		node* temp1;
		node* temp2;
		temp1=hashMap[i];
		while(temp1!=NULL){
		temp2=temp1;
		temp1=temp1->next;
		free(temp2);		
		}
	}
	}
	free(hashMap);
	return;
}
int main(int argc, char** argv){
	FILE* fp;
	fp=fopen(argv[1],"r");
	node** hashMap=malloc(1000*sizeof(node*));
	if(fp==NULL){
	printf("File not found");
	return 0;
	}
	int num;
	char command;
	if(fscanf(fp,"%c\t%d\n",&command,&num)==EOF){
		printf("End of file");
		return 0;
	}
	if(command=='i'){
		insert(num,hashMap);
	} else if(command=='s'){
		search(num,hashMap);
	}
	while(fscanf(fp,"%c\t%d\n",&command,&num)!=EOF){
		if(command=='i'){
			insert(num,hashMap);
		}
		if(command=='s'){
			search(num,hashMap);
		}
	}
	fclose(fp);
	deleteTable(hashMap);

	return 0;
}
