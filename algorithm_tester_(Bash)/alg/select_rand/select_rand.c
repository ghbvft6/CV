#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int cmps;

int partition_rand(int *a, int first, int last){
	int pivot=rand()%(last-first+1)+first;
	int tmp;
	tmp=a[last];
	a[last]=a[pivot];
	a[pivot]=tmp;
	int i=first+1;
	while(i<last){
//printf_arr(a);
		++cmps;
		if(a[i]<a[last]){
			tmp=a[i];
			a[i]=a[first];
			a[first]=tmp;
			++first;
		}
		++i;
	}
	tmp=a[last];
	a[last]=a[first+1];
	a[first+1]=tmp;
	return first+1;
}

int n;

void printf_arr(int *arr){
	int t=0;
	while(t<n) printf("%d ", arr[t]),t++;
	puts("");
}

int select_rand(int *a, int first, int last, int k){
	//puts("");
//printf_arr(a);
	if(first==last) return a[first];
	int pivot=partition_rand(a, first, last);
	if(pivot==k) return a[k];
	int move=pivot-first+1;
	if(k<=move) return select_rand(a, first, move, k);
	else return select_rand(a, move+1, last, k-move); 
}

int main(){
	srand(time(NULL));

	int k;


	cmps=0;
	//int n
int *ptr;
	scanf("%d", &n);
scanf("%d", &k);

	int *arr=NULL;
	arr=malloc(n*sizeof(int));
	if(arr==NULL){ printf("out of memory"); return 0;}

	ptr=arr+n;
	while(ptr!=arr) --ptr, scanf("%d", ptr);

	/*ptr=arr;
	int ptrlim=ptr+n;
	while(ptr!=ptr_lim){
		printf("%d ", *ptr);
		++ptr;
	}*/
	printf("%d",select_rand(arr, 0, n-1, k));

	FILE *file;
	file = fopen("file.txt","w"); /* apend file (add text to
a file or create a file if it does not exist.*/
fprintf(file,"%d\n",cmps); /*writes*/
fclose(file); /*done!*/ 
return 0;
}
