#include<stdlib.h>
#include<stdio.h>
#include<string.h>

char* notVowel(char*);
char* vowel(char*);
char* vowel(char* string){
	char* temp1=malloc(sizeof(char)*10000);
	temp1=strcpy(temp1,string);
	char* temp2="yay\0";
	char* result=malloc(2*sizeof(temp1));
	result=strcat(temp1, temp2);
	return result;
}
char* notVowel(char* string){
	char* temp1=malloc(sizeof(char)*10000);
	int i=0;
	int k=strlen(string);
	char* tempString=malloc(sizeof(char)*10000);
	tempString=strcpy(tempString,string);
	for(i=i;i<k-1;i++){
		if(string[i]=='e'||
		string[i]=='i'||
		string[i]=='o'||
		string[i]=='u'||
		string[i]=='a'||
		string[i]=='E'||
		string[i]=='I'||
		string[i]=='O'||
		string[i]=='U'||
		string[i]=='A'){
		break;
		}
	}
	int l=0;
	for(int j=i;l<k-1;j++){
		temp1[l]=tempString[j];
		l++;
	}
	char* temp2="ay";
	char* result="";
	result=strncat(temp1,tempString,i);
	result=strcat(result,temp2);
	return result;
}
int main(int argc, char** argv){
	if(argc==1){
	return 0;
	}
	char** pigLatin=malloc(sizeof(char*)*argc);
	char* string=malloc(sizeof(char*)*1000);
	for(int i=1;argv[i]!='\0';i++){
		string=argv[i];
		if(string[0]=='e'||
		string[0]=='i'||
		string[0]=='o'||
		string[0]=='u'||
		string[0]=='a'||
		string[0]=='E'||
		string[0]=='I'||
		string[0]=='O'||
		string[0]=='U'||
		string[0]=='A'){
		pigLatin[i-1]=vowel(string);
		} else {
			pigLatin[i-1]=notVowel(string);
		}
	}
	for(int i=0;i<argc-2;i++){
		printf("%s ",pigLatin[i]);
	}
	printf("%s",pigLatin[argc-2]);
	free(pigLatin);
return 0;
}
