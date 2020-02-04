#include<stdlib.h>
#include<stdio.h>
int* fillRow(int,int,FILE*);
void counterReset(int*);

int* fillRow(int rowNumber,int n,FILE* fp){
int* row=malloc(n*sizeof(int));
int k;
for(int i=0;i<n;i++){
	fscanf(fp,"%d\t",&k);
	row[i]=k;
}
fscanf(fp,"\n");
return row;
}
void counterReset(int* counter){
for(int i=0;i<10000;i++){
	counter[i]=0;
}
return;
}


int main(int argc, char** argv){
	FILE* fp;
	fp=fopen(argv[1],"r");
	if(fp==NULL){
		printf("File is invalid");
		return 0;
		}
	int n;
	if(fscanf(fp,"%d\n",&n)==EOF){
		printf("End of file");
		return 0;
		}
	if(n==1){
		printf("magic\n");
		return 0;
		}
	int** row=malloc(n*sizeof(int*));
	int* counter=malloc(10000*sizeof(int));
	counterReset(counter);
	for(int i=0;i<n;i++){
		row[i]=fillRow(i,n,fp);
		}
	int check=0;
	for(int i=0;i<n;i++){
		check+=row[0][i];
		}
	int comp=0;
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			comp+=row[i][j];
			if(counter[row[i][j]]==1){
			printf("not-magic\n");
			return 0;
			} else {
			counter[row[i][j]]=1;
			}
		}
		if(comp!=check){
		printf("not-magic\n");
		return 0;
		}
		comp=0;
	}
	counterReset(counter);
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			comp+=row[j][i];
			if(counter[row[j][i]]==1){
			printf("not-magic\n");
			return 0;
			} else {
			counter[row[j][i]]=1;
			}
			}
		if(comp!=check){
		printf("not-magic\n");
		return 0;
		}
		comp=0;
	}
	counterReset(counter);
	int j=0;
	for(int i=0;i<n;i++){
	comp+=row[j][i];
	if(counter[row[j][i]]==1){
			printf("not-magic");
			return 0;
			} else {
			counter[row[j][i]]=1;
			}
	j++;
	}
	if(comp!=check){
	printf("not-magic\n");
	return 0;		
	}
	counterReset(counter);
	comp=0;
	j=n-1;
	for(int i=0;i<n;i++){
	comp+=row[i][j];
	if(counter[row[i][j]]==1){
			printf("not-magic");
			return 0;
			} else {
			counter[row[i][j]]=1;
			}
	j--;
	}
	if(comp!=check){
	printf("not-magic\n");
	return 0;		
	}
	printf("magic\n");
	fclose(fp);
	free(row);
	return 0;
}
