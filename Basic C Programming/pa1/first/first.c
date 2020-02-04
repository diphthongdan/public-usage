#include <stdlib.h>
#include <stdio.h>

int isPrime(int x);

int main(int argc, char** argv){
FILE *fp;
fp=fopen(argv[1],"r");
if(fp==NULL){
	printf("File could not be found\n");
	exit(0);
}
int num;
if(fscanf(fp,"%d\n",&num)== EOF){
printf("Empty File\n");
}
for(int i=0;i<num;i++){
	int n;
	fscanf(fp,"%d\n",&n);
	if(n<=0){
	printf("no\n");
	}
	while(n!=0){
		int true=isPrime(n);
		if(true==0){
		printf("no\n");
		break;
		}
		n=n/10;
		if(n==0){
		printf("yes\n");
		break;
		}
	}
}
return 0;
}

int isPrime(int x){
	if(x==1){
	return 0;
	}
	if((x%2==0)&&(x==2)){
	return 0;
	}
	int i;
	for(i=3;i<=x/2;i++){
		if(x%i==0){
		return 0;}
	}
	return 1;
}
