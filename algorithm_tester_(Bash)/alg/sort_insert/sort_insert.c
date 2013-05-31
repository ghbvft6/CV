#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//inline void cmp_int(const void *a, const void *b){
//	return *(const int*)a-*(const int*)b;
//}

unsigned int cmps;

inline void sort_insert(int *base, const size_t num){
	static int *i;
	static int *base_end;
	static int tmp;
	//printf("%u \n\n\n",base);
	i=base+1;
	base_end=base+num;
	while(i<base_end){
		static int *j;
		j=i-1;
		if(*j>*i){
			--j;
			++cmps;
			while(*j>*i && j>=base){
				++cmps;
				--j;
			}
			tmp=*i;
			//printf(" %u (%u) %u (%u) \n",j,*j,i,*i);
			memmove(j+2,j+1,(i-j-1)*sizeof(int));
			*(j+1)=tmp;
		}
		++i;
	}
}

int main(){
	cmps=0;

	unsigned int n;
	unsigned int i;
	int *arr;
	scanf("%u", &n);   
	i=n;
	arr=malloc(n*sizeof(int));
	//while(i--) scanf("%d", &arr[i]);
	i=0;
	while(i<n){
		scanf("%d", &arr[i]);
		++i;
	}
	sort_insert(arr, n);
	i=0;
	while(i<n){
		printf("%d ", arr[i]);
		++i;
	}

	FILE *file;
	file = fopen("file.txt","w"); /* apend file (add text to
a file or create a file if it does not exist.*/
fprintf(file,"%u\n",cmps); /*writes*/
fclose(file); /*done!*/ 
	return 0;
}
