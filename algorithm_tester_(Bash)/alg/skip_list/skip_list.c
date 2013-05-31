#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <math.h>

#define print1

int cmpsadd;
int cmpsdel;
int maxcmpsadd;
int maxcmpsdel;
int ccmps;


typedef struct NODE
{
	int value;
	struct NODE **forward;
} NODE;

NODE *header;

int skipsize;
int maxlevel;

int newlevel(){
	int log2size=0;
	int skipsize2=skipsize;
	while(skipsize2){
		skipsize2>>=1;
		++log2size;
	}
	return log2size+1;
}



void add(int value){
	ccmps=0;
	int level=1;
	
	while(rand()%2 && level<maxlevel) ++level;

	NODE *newnode;
	newnode=malloc(sizeof(NODE));
	newnode->value=value;
	newnode->forward=malloc(sizeof(NODE*)*level);

	int i=maxlevel;
	NODE *node=header;
	NODE **update=malloc(sizeof(NODE*)*maxlevel);
	while(i--){
		++ccmps;
		while(node->forward[i]->value<value){
			++ccmps;
			//printf("%d %d\n", value, node->forward[i]->value);
			node=node->forward[i];
		}
		update[i]=node;		
	}

	while(level--){
		newnode->forward[level]=update[level]->forward[level];
		update[level]->forward[level]=newnode;
	}
	free(update);

	++skipsize;
	maxlevel=newlevel();
	header->forward=realloc(header->forward, sizeof(NODE*)*(maxlevel+1));
	header->forward[maxlevel]=header;

	if(ccmps>maxcmpsadd) maxcmpsadd=ccmps;
	cmpsadd+=ccmps;
}

void delete(int value){
	ccmps=0;
	int i=maxlevel;
	NODE *node=header;
	NODE **update=malloc(sizeof(NODE*)*maxlevel);
	int level=0;
	while(i--){
		++ccmps;
		while(node->forward[i]->value<value){
			++ccmps;
			//printf("%d %d\n", value, node->forward[i]->value);
			node=node->forward[i];
		}
		if(level==0 && node->forward[i]->value==value) level=i+1;
		update[i]=node;		
	}
	
	if(level==0) return;	

	NODE *oldnode=node->forward[0];

	while(level--){
		update[level]->forward[level]=oldnode->forward[level];
	}
	free(update);
	free(oldnode->forward);
	free(oldnode);

	--skipsize;
	maxlevel=newlevel();
	header->forward=realloc(header->forward, sizeof(NODE*)*(maxlevel+1));

	if(ccmps>maxcmpsdel) maxcmpsdel=ccmps;
	cmpsdel+=ccmps;
}

void printthelist(int value){
	NODE *node=header->forward[0];
	while(node!=header){
		if(node->value==value) printf("[%d] ", node->value);
		else printf("%d ", node->value);
		node=node->forward[0];
	}
}

int main(){
	int n, seed, ntmp;
	scanf("%d%d", &n, &seed);
	srand(seed);
	ntmp=n;
	int arr[n];
	cmpsadd=cmpsdel=maxcmpsadd=maxcmpsdel=ccmps=0;

	skipsize=0;
	maxlevel=1;
	header=malloc(sizeof(NODE));
	header->value=20000000;
	header->forward=malloc(sizeof(NODE*)*(maxlevel+1));
	header->forward[0]=header;
	header->forward[maxlevel]=header;
	
	int tmp;

	while(n--){
		tmp=rand()%10000000;
		arr[n]=tmp;
		add(tmp);
	#ifdef print
		printthelist(tmp);
		puts("");
	#endif
	}
puts("");
	n=ntmp;
	while(n--){
		delete(arr[n]);
	#ifdef print
		printthelist(arr[n-1]);
		puts("");
	#endif
	}

	n=ntmp;
	int log2n=0;
	while(n>>=1) ++log2n;
	printf("log2(n) %d\n\nadd avg %d\nadd max %d\ndel avg %d\ndel max %d\n",log2n,cmpsadd/ntmp,maxcmpsadd,cmpsdel/ntmp,maxcmpsdel);
}


