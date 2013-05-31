#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define MAX 100000
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
	int tab_max=tab[0];
	i=1;
	while(i<n){
		if(tab[i]>tab_max) tab_max=tab[i];
		++i;
	}
	//printf("%d",tab_max);
	//return 0;
	//int counted[MAX]={0};
	int *counted;
	counted = malloc(10*sizeof(int));
		int *tab2; /*out*/
		tab2=malloc(n*sizeof(int));
	int power_10=1;
	while(tab_max/power_10){
		memset(counted,0,sizeof(int)*10);
		i=0;
		while(i<n){
			++counted[(tab[i]/power_10)%10];
			++i;
		}
		int sum;
		int tmp;
		sum=0;
		i=0;
		while(i<10){
			tmp=counted[i];
			counted[i]=sum;
			sum+=tmp;
			++i;
		}
		/**/
		i=0;
		while(i<n){
			tab2[counted[(tab[i]/power_10)%10]]=tab[i];
			++counted[(tab[i]/power_10)%10];
			++i;
		}
		int *ptr_t;
		ptr_t=tab;
		tab=tab2;
		tab2=ptr_t;
		power_10*=10;
		i=0;
		while(i<n){
			printf("%d ",tab[i]); //tab
			++i;
		}
	}
	i=0;
	while(i<n){
		printf("%d ",tab[i]); //tab
		++i;
	}
	return 0;
}
