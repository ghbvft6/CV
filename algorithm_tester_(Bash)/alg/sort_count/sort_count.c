#include <stdlib.h>
#include <stdio.h>
#define MAX 10000001
int main(){
	int *tab;
	int n;
	scanf("%d", &n);
	tab=malloc(n*sizeof(int));
	int i;
	i=0;
	while(i<n){
		scanf("%d", &tab[i]);
		++i;
	}
	//int counted[MAX]={0};
	int *counted;
	counted = calloc(MAX,sizeof(int));
	i=0;
	while(i<n){
		++counted[tab[i]];
		++i;
	}
	int sum;
	int tmp;
	sum=0;
	i=0;
	while(i<=MAX){
		tmp=counted[i];
		counted[i]=sum;
		sum+=tmp;
		++i;
	}
	int *tab2;
	tab2=malloc(n*sizeof(int));
	i=0;
	while(i<n){
		tab2[counted[tab[i]]]=tab[i];
		++counted[tab[i]];
		++i;
	}
	i=0;
	while(i<n){
		printf("%d ",tab2[i]);
		++i;
	}
	return 0;
}
