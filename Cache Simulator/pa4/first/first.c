#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct blocks{
	int valid;
	unsigned long long int tag;
	int counter;
} block;
typedef struct sets{
	int openBlocks;
	int bigCounter;//represents total number of blocks added, used for FIFO
	block* bArray;
} set;
void freeCache(set*,int);
set* makeCache(int,int,int,int);
int assocCheck(char*);
int valueCheck(int);
void searchCache(set*,unsigned long long int, int*, int*,int*,int,int,int,int,int,int);
int myLog(int);
void printResults(int,int*,int*,int*,int);
void prefetchMiss(set*,unsigned long long int, int*, int,int,int,int,int,int);
int modeCheck(char*);
void freeCache(set* cache,int sSize){
	for(int i=0;i<sSize;i++){
		free(cache[i].bArray);
	}
	free(cache);
	return;
}
int modeCheck(char* string){
	char* string1="fifo";
	char* string2="lru";
	if(strcmp(string,string1)==0){
		return 0;
	}
	if(strcmp(string,string2)==0){
		return 1;
	}
	return 2;
}
void prefetchMiss(set* cache,unsigned long long int address, int* reads,int mode,int bBits,int sBits,int assoc,int sSize,int lru){
	int index=(address>>bBits)%sSize;
	unsigned long long int tag=(address>>bBits)>>sBits;
	for(int i=0;i<assoc;i++){ //checks for hit
		if(cache[index].bArray[i].tag==tag&&cache[index].bArray[i].valid==1){
			if(lru==1){
			cache[index].bigCounter++;
			cache[index].bArray[i].counter=cache[index].bigCounter;
			}
			return;
		}
	}
	if(cache[index].openBlocks==0){ //Set is full
		int x=0;
		for(int i=0;i<assoc;i++){
			if(cache[index].bArray[i].counter<cache[index].bArray[x].counter){//find first entered block
				x=i;
			}
		}
		reads[mode]++;
		cache[index].bigCounter++;
		cache[index].bArray[x].tag=tag;
		cache[index].bArray[x].counter=cache[index].bigCounter;
		return;
	} else{ //set is not full
		for(int i=0;i<assoc;i++){
			if(cache[index].bArray[i].valid==0){
				cache[index].bigCounter++;
				cache[index].bArray[i].valid=1;
				cache[index].bArray[i].tag=tag;
				cache[index].bArray[i].counter=cache[index].bigCounter;
				reads[mode]++;
				cache[index].openBlocks--;
				return;
			}
		}
	}
	
	return;
}
void printResults(int mode,int* hits,int* miss,int* reads,int writes){
	if(mode==0){
		printf("no-prefetch\n");
	}
	if(mode==1){
		printf("with-prefetch\n");
	}
	printf("Memory reads: %d\n",reads[mode]);
	printf("Memory writes: %d\n",writes);
	printf("Cache hits: %d\n",hits[mode]);
	printf("Cache misses: %d\n",miss[mode]);
}
int myLog(int x){ //base 2 log function
	int y=0;
	for(int i=0;x!=1;i++){
		y++;
		x=x/2;
	}
	return y;
}
void searchCache(set* cache,unsigned long long int address, int* hits, int* miss,int* reads,int mode,int bSize,int sSize,int assoc,int pSize,int lru){
	int sBits=myLog(sSize);
	int bBits=myLog(bSize);
	int index=(address>>bBits)%sSize;
	unsigned long long int tag=(address>>bBits)>>sBits;
	for(int i=0;i<assoc;i++){ //checks for hit
		if(cache[index].bArray[i].tag==tag&&cache[index].bArray[i].valid==1){
			hits[mode]++;
			if(lru==1){
			cache[index].bigCounter++;
			cache[index].bArray[i].counter=cache[index].bigCounter;
			}
			return;
		}
	}
	if(cache[index].openBlocks==0){ //Set is full
		int x=0;
		for(int i=0;i<assoc;i++){
			if(cache[index].bArray[i].counter<cache[index].bArray[x].counter){//find first entered block
				x=i;
			}
		}
		miss[mode]++;
		reads[mode]++;
		cache[index].bigCounter++;
		cache[index].bArray[x].tag=tag;
		cache[index].bArray[x].counter=cache[index].bigCounter;
		if(mode==1){
			for(int i=0;i<=pSize;i++){
				prefetchMiss(cache,address+(bSize*i),reads,1,bBits,sBits,assoc,sSize,lru);
			}
		}
		return;
	} else{ //set is not full
		for(int i=0;i<assoc;i++){
			if(cache[index].bArray[i].valid==0){
				cache[index].bigCounter++;
				cache[index].bArray[i].valid=1;
				cache[index].bArray[i].tag=tag;
				cache[index].bArray[i].counter=cache[index].bigCounter;
				miss[mode]++;
				reads[mode]++;
				cache[index].openBlocks--;
				if(mode==1){
					for(int i=0;i<=pSize;i++){
						prefetchMiss(cache,address+(bSize*i),reads,1,bBits,sBits,assoc,sSize,lru);
					}
				}
				return;
			}
		}
	}
	
	return;
}
int valueCheck(int x){
	if(x==0){
		return 0;
	}
	while(x!=1){
		if(x%2!=0){
			return 0;
		}
		x=x/2;
	}
	return 1;
}
int assocCheck(char* string){
	if(string[0]=='d'){
		if(strlen(string)==6){
			return 1; //direct mapped
		} else{
			return 0;//not valid input
		}
	}
	char* string2="assoc";
	if(strlen(string)<5){
			return 0;//not valid input
		}
	if(strlen(string)==5){
		if(strcmp(string,string2)==0){
			return -1;//Fully associative
		}
	}
	if(strlen(string)>5){
		string2="assoc:";
		if(memcmp(string,string2,6)!=0){
			return 0;//not valid input
			}
		string2=strtok(string,":");
		string2=strtok(NULL,"s");
		int n=atoi(string2); //n way associativity
		return n;
	}
	return 0;
}
set* makeCache(int sSize,int bSize,int assoc,int pSize){
	set* sArray=malloc(sizeof(set)*sSize);
	for(int i=0;i<sSize;i++){
		sArray[i].openBlocks=assoc;
		sArray[i].bigCounter=0;
		sArray[i].bArray=malloc(sizeof(block)*assoc);
		for(int j=0;j<assoc;j++){
			sArray[i].bArray[j].valid=0;
			sArray[i].bArray[j].counter=0;
			sArray[i].bArray[j].tag=0;
		}
	}
	return sArray;
}
int main(int argc, char** argv){
	int writes=0;
	int* reads=malloc(sizeof(int)*2);
	int* hits=malloc(sizeof(int)*2);
	int* miss=malloc(sizeof(int)*2);
	for(int i=0;i<2;i++){
	hits[i]=0;
	reads[i]=0;
	miss[i]=0;
	}
	int cache_size=atoi(argv[1]);
	int bSize=atoi(argv[2]);
	int assoc=assocCheck(argv[4]);
	int pSize=atoi(argv[5]);
	int sSize;
	int lru=modeCheck(argv[3]);
	if(lru==2){
		printf("error\n");
		return 0;
	}
	if(assoc==0){
		printf("error\n");
		return 0;
	}
	if(assoc==-1){
		assoc=cache_size/bSize;
		sSize=1;
	} else{
		sSize=(cache_size/assoc)/bSize;
	}
	if(!valueCheck(cache_size)){
		printf("error\n");
		return 0;
	}
	if(!valueCheck(assoc)){
		printf("error\n");
		return 0;
	}
	if(!valueCheck(bSize)){
		printf("error\n");
		return 0;
	}
	set* cache=makeCache(sSize,bSize,assoc,pSize);
	set* pCache=makeCache(sSize,bSize,assoc,pSize);
	FILE* fp=fopen(argv[6],"r");
	if(fp==NULL){
		printf("error\n");
		return 0;
	}
	unsigned long long int address;
	char command;
	while(fscanf(fp, "%c%llx", &command, &address)!=EOF){
		if(command =='#'){
			break;
		}
		if(command =='W'){
			writes++;
		}
		searchCache(cache,address,hits,miss,reads,0,bSize,sSize,assoc,pSize,lru);
		searchCache(pCache,address,hits,miss,reads,1,bSize,sSize,assoc,pSize,lru);
		fscanf(fp,"\n");
	}
	printResults(0,hits,miss,reads,writes);
	printResults(1,hits,miss,reads,writes);
	free(hits);
	free(miss);
	free(reads);
	freeCache(cache,sSize);
	freeCache(pCache,sSize);
	fclose(fp);
	return 0;
}
