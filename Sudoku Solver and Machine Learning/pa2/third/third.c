#include<stdio.h>
#include<stdlib.h>
double* fillRow(int,int,FILE*,double**);
double** multiplyMatrices(double**,double**,int,int,int);
double** invertMatrix(double**,int);
void freeMatrix(double**,int);
void freeMatrix(double** matrix, int rows){
	for(int i=0;i<rows;i++){
		free(matrix[i]);
		}
	free(matrix);
}
double** multiplyMatrices(double** transposed,double** original,int m,int n,int y){
	double ** multipliedMatrix=malloc((n)*sizeof(double*));
	for(int i=0;i<n;i++){
			multipliedMatrix[i]=malloc(sizeof(double)*(y));
			for(int j=0;j<y;j++){
				double result=0;
				for(int k=0;k<m;k++){
				result+=transposed[i][k]*original[k][j];
				}
				multipliedMatrix[i][j]=result;
			}
		}
	return multipliedMatrix;
}
double** invertMatrix(double** matrix,int n){
	double** identity=malloc((n+1)*sizeof(double*));
	for(int i=0;i<n+1;i++){
		identity[i]=malloc((n+1)*sizeof(double*));
		for(int j=0;j<n+1;j++){
			if(j==i){
			identity[i][j]=1;
			} else {
			identity[i][j]=0;
			}
		}
	}
	for(int i=0;i<n+1;i++){
		for(int j=0;j<n+1;j++){
			if(i!=j){
				double factor=matrix[j][i]/matrix[i][i];
				for(int x=0;x<n+1;x++){
					matrix[j][x]=matrix[j][x]-(matrix[i][x]*factor);
					identity[j][x]=identity[j][x]-(identity[i][x]*factor);
				}
			} else {
				double factor=matrix[i][j];
				for(int x=0;x<n+1;x++){
					matrix[i][x]=matrix[i][x]*(1/factor);
					identity[i][x]=identity[i][x]*(1/factor);
				}
			}
		}
	}
	return identity;
}
double* fillRow(int rowNumber,int n,FILE* fp,double** housePrice){
	double* row=malloc((n+1)*sizeof(double));
	row[0]=1;
	double k;
	for(int i=0;i<n;i++){
		fscanf(fp,"%lf,",&k);
		row[i+1]=k;
	}
	fscanf(fp,"%lf\n",&k);
	housePrice[rowNumber]=malloc(sizeof(double));
	housePrice[rowNumber][0]=k;
	return row;
}

int main(int argc, char** argv){
	FILE* fp;
	fp=fopen(argv[1],"r");
	if(fp==NULL){
		printf("No file found");
	}
	int attributes,tSets;
	fscanf(fp,"%d\n%d\n",&attributes,&tSets);
	double** attributeMatrix=malloc(tSets*sizeof(double*));
	double** housePrice=malloc(tSets*sizeof(double*));
	for(int i=0;i<tSets;i++){
		attributeMatrix[i]=fillRow(i,attributes,fp,housePrice);
	}
	double** transposedAttribute=malloc((attributes+1)*sizeof(double*));
	for(int i=0;i<attributes+1;i++){
		transposedAttribute[i]=malloc(tSets*sizeof(double));
		for(int j=0;j<tSets;j++){
			transposedAttribute[i][j]=attributeMatrix[j][i];
		}
	}
	double** multipliedMatrix=multiplyMatrices(transposedAttribute,attributeMatrix,tSets,attributes+1,attributes+1);
	double** inverseMatrix=invertMatrix(multipliedMatrix,attributes);
	double** multipliedMatrix2=multiplyMatrices(inverseMatrix,transposedAttribute,attributes+1,attributes+1,tSets);
	double** multipliedMatrix3=multiplyMatrices(multipliedMatrix2,housePrice,tSets,attributes+1,1);
	fclose(fp);
	fp=fopen(argv[2],"r");
	if(fp==NULL){
		printf("No file found");
	}
	int houses;
	fscanf(fp,"%d\n",&houses);
	for(int i=0;i<houses;i++){
		double price=0;
		double k;
		for(int j=0;j<attributes+1;j++){
			if(j==0){
			price+=multipliedMatrix3[j][0];
			continue;
			}
			fscanf(fp,"%lf,",&k);
			price+=k*multipliedMatrix3[j][0];
		}
	printf("%0.0lf\n",price);
	}
	fclose(fp);
	freeMatrix(housePrice,tSets);
	freeMatrix(inverseMatrix,attributes+1);
	freeMatrix(attributeMatrix,tSets);
	freeMatrix(transposedAttribute,attributes+1);
	freeMatrix(multipliedMatrix,attributes+1);
	freeMatrix(multipliedMatrix2,attributes+1);
	freeMatrix(multipliedMatrix3,attributes+1);
	return 0;
}
