#include<stdio.h>
#include<stdlib.h>

char* fillRow(FILE*);
void freePuzzle(char**);
int solvePuzzle(char**);
int rowCheck(char, char**,int);
int columnCheck(char, char**,int);
int checkPuzzle(char**);
int isValid(char,char**,int,int);
int solutionCheck(char**);
int possibleSolutions(char,char**,int,int);
void clearCheck(int*);
void freePuzzle(char** puzzle){
	for(int i=0;i<16;i++){
		free(puzzle[i]);
	}
	free(puzzle);
}
int possibleSolutions(char bit, char** puzzle,int i,int j){
	int solutionFound=0;
	for(int k=0;k<16;k++){
		if(isValid(bit,puzzle,i,j)==1){
			solutionFound++;
			}
		if(bit=='9'){
			bit+=7;
		}	
			bit++;
		}
	return solutionFound;
}
void clearCheck(int* check){
	for(int i=0;i<100;i++){
		check[i]=0;
	}
	return;
}
int solutionCheck(char** puzzle){
	int check[100];
	clearCheck(check);
	for(int i=0;i<16;i++){
		for(int j=0;j<16;j++){
			int x=puzzle[i][j];
			if(check[x]==1){
				return 0;
			}
			check[x]=1;	
		}
		clearCheck(check);
	}
	for(int i=0;i<16;i++){
		for(int j=0;j<16;j++){
			int x=puzzle[i][j];
			if(check[x]==1){
				return 0;
			}
			check[x]=1;	
		}
		clearCheck(check);
	}
	return 1;
}
int checkPuzzle(char** puzzle){
	for(int i=0;i<16;i++){
		for(int j=0;j<16;j++){
			if(puzzle[i][j]=='-'){
			return 0;
			}	
		}
	}
	return 1;
}
int solvePuzzle(char** puzzle){
	int solutionFound=0;
	for(int i=0;i<16;i++){
		for(int j=0;j<16;j++){
			if(puzzle[i][j]=='-'){
				char bit='0';
				if(possibleSolutions(bit,puzzle,i,j)!=1){
				continue;
				} else {
				for(int k=0;k<16;k++){
					if(isValid(bit,puzzle,i,j)==1){
						puzzle[i][j]=bit;
						solutionFound++;
						break;
					}
					if(bit=='9'){
						bit+=7;
					}
					bit++;
				}
				}
			}
		}
	}
	if(solutionFound==0){
		return 0;
	}
	return 1;
}
int isValid(char bit,char** puzzle, int row, int column){
	if(rowCheck(bit,puzzle,row)==1&&columnCheck(bit,puzzle,column)==1){
		return 1;
	}
	return 0;
}
int rowCheck(char bit,char** puzzle,int row){
	int check[100];
	clearCheck(check);
	for(int i=0;i<16;i++){
		int x=puzzle[row][i];
		check[x]=1;
		if(puzzle[row][i]==bit){
			return 0;
		}
	}
	int x=bit;
	if(check[x]==1){
		clearCheck(check);
		return 0;
	}
	return 1;
}
int columnCheck(char bit,char** puzzle,int column){
	int check[100];
	clearCheck(check);
	for(int i=0;i<16;i++){
		int x=puzzle[i][column];
		check[x]=1;
		if(puzzle[i][column]==bit){
			return 0;
		}
	}
	int x=bit;
	if(check[x]==1){
		clearCheck(check);
		return 0;
	}
	return 1;
}
char* fillRow(FILE* fp){
	char* row=malloc(16*sizeof(char));
	char k;
	for(int i=0;i<16;i++){
		fscanf(fp,"%c\t",&k);
		row[i]=k;
		}
	fscanf(fp,"\n");
	return row;
}
int main(int argc,char** argv){
	FILE* fp;
	fp=fopen(argv[1],"r");
	if(fp==NULL){
		printf("No file found\n");
		fclose(fp);
		return 0;
	}
	char** puzzle=malloc(sizeof(char*)*16);
	int i=0;
	while(i<16){
		puzzle[i]=fillRow(fp);
		i++;
	}
	while(checkPuzzle(puzzle)!=1){
		if(solvePuzzle(puzzle)==0){
			printf("no-solution\n");
			freePuzzle(puzzle);
			return 0;
		}
	}
	if(solutionCheck(puzzle)==0){
		printf("no-solution\n");
		freePuzzle(puzzle);
		return 0;
	}
	for(int i=0;i<16;i++){
		for(int j=0;j<16;j++){
			printf("%c\t",puzzle[i][j]);	
		}
		printf("\n");
	}
	fclose(fp);
	freePuzzle(puzzle);
	return 0;
}
