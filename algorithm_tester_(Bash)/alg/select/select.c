#include <stdio.h>
#include <stdlib.h>

int cmps;

int cmp(const void *a, const void *b){
	++cmps;
	return (*(int*)a-*(int*)b);
}

int main(){
	int k;
	

	cmps=0;
	int n, *ptr;
	scanf("%d", &n);
scanf("%d", &k);
	int *arr=NULL;
	arr=malloc(n*sizeof(int));
	if(arr==NULL){ printf("out of memory"); return 0;}

	ptr=arr+n;
	while(ptr!=arr) --ptr, scanf("%d", ptr);

	qsort (arr, n, sizeof(int), cmp);

	/*ptr=arr;
	int ptrlim=ptr+n;
	while(ptr!=ptr_lim){
		printf("%d ", *ptr);
		++ptr;
	}*/
	printf("%d",arr[k]);

	FILE *file;
	file = fopen("file.txt","w"); /* apend file (add text to
a file or create a file if it does not exist.*/
fprintf(file,"%d\n",cmps); /*writes*/
fclose(file); /*done!*/ 
return 0;
}
