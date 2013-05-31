#include <stdio.h>
#include <stdlib.h>

int cmps;

int cmp(const void *a, const void *b){
	++cmps;
	return (*(int*)a-*(int*)b);
}

int main(){
	cmps=0;
	int n, *ptr;
	scanf("%d", &n);

	int *arr=NULL;
	arr=malloc(n*sizeof(int));
	if(arr==NULL){ printf("out of memory"); return 0;}

	ptr=arr;
	int *ptr_lim=ptr+n;
	while(ptr!=ptr_lim){
		scanf("%d", ptr);
		++ptr;
	}

	qsort (arr, n, sizeof(int), cmp);

	ptr=arr;
	int *ptr_lim=ptr+n;
	while(ptr!=ptr_lim){
		printf("%d ", *ptr);
		++ptr;
	}

	FILE *file;
	file = fopen("file.txt","w"); /* apend file (add text to
a file or create a file if it does not exist.*/
fprintf(file,"%d\n",cmps); /*writes*/
fclose(file); /*done!*/ 
return 0;
}
