#include<stdlib.h>
#include<stdio.h>
int* fillRow(int,int,FILE*);
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
int main(int argc, char** argv){
	FILE* fp;
	fp=fopen(argv[1],"r");
	int n,m;
	if(fp==NULL){
		printf("Empty file");
		return 0;
	}
	if(fscanf(fp,"%d\t%d\n",&n,&m)==EOF){
		printf("End of file");
		return 0;
	}
	int** matrix1=malloc(n*sizeof(int*));
	for(int i=0;i<n;i++){
		matrix1[i]=fillRow(i,m,fp);
	}
	int x,y;
	fscanf(fp,"\n%d\t%d\n",&x,&y);
	int** matrix2=malloc(x*sizeof(int*));
	for(int i=0;i<x;i++){
		matrix2[i]=fillRow(i,y,fp);
	}
	if(m!=x){
		printf("bad-matrices\n");
		for(int i=0;i<x;i++){
		free(matrix2[i]);
		}
		for(int i=0;i<n;i++){
		free(matrix1[i]);
		}
		free(matrix1);
		free(matrix2);
		return 0;
	}
	int ** matrixResult=malloc(sizeof(int*)*n);
	if(m==x){
		for(int i=0;i<n;i++){
			matrixResult[i]=malloc(sizeof(int)*y);
			for(int j=0;j<y;j++){
				int result=0;
				for(int k=0;k<m;k++){
				result+=matrix1[i][k]*matrix2[k][j];
				}
				matrixResult[i][j]=result;
			}
		}
	}
	for(int i=0;i<n;i++){
		for(int j=0;j<y;j++){
			printf("%d\t",matrixResult[i][j]);
		}
		printf("\n");
	}
	return 0;	
}
