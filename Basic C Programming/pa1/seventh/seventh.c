#include<stdlib.h>
#include<stdio.h>
#include<string.h>
int main(int argc, char**argv){
	if(argc==1){
	return 0;
	}
	char* string=malloc(sizeof(char)*1000);
	for(int i=1; i<argc;i++){
		char* temp=argv[i];
		char lastLetter;
		int j;
		for(j=0;temp[j]!='\0';j++){
		}
		lastLetter=temp[j-1];
		string[i-1]=lastLetter;
	}
	printf("%s",string);
	free(string);

return 0;
}
