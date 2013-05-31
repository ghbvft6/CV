#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INT (unsigned int)-1

int cmps;

void swap(int *a, int *b){
	printf("AAAAAAA");
	int *t;
	*t=*a;
	*a=*b;
	*b=*t;
}

/*inline void heap_check_down(int *arr, size_t i){
	int i2=i<<1;
	cmps+=2;
	if(arr[i]<arr[i2] && arr[i2]>arr[i2+1]){
		--cmps;
		swap(arr+i, arr+i2);
		if(i>1) heap_check_down(arr, i>>1);
	} else if(arr[i]<arr[i2+1] && arr[i2+1]>arr[i2]){
		swap(arr+i,arr+i2+1);
		if(i>1) heap_check_down(arr, i>>1);
	}
}*/

inline void heap_check_up(int *arr, size_t i){
	int i2=i>>1;
	++cmps;
	//printf("%d\n",i);
	if(i>1 && arr[i]>arr[i2]){
		//printf("%d %d\n",i,i2);
		//swap(arr+i, arr+i2);
	//printf("AAAAAAA");
		int t = arr[i];
		arr[i]=arr[i2];
		arr[i2]=t;
		heap_check_up(arr, i2);
	}
}

inline void heap_check_down(int *arr, size_t i, size_t i_last){
	int i2=i<<1;
	++cmps;
	if(i2<i_last && (arr[i]<arr[i2] || arr[i]<arr[i2+1])){
		++cmps;
		if(arr[i2]>arr[i2+1]){
			//swap(arr+i, arr+i2);
			int t = arr[i];
			arr[i]=arr[i2];
			arr[i2]=t;
			heap_check_down(arr, i2, i_last);
		} else{
			//swap(arr+i, arr+i2+1);
			int t = arr[i];
			arr[i]=arr[i2+1];
			arr[i2+1]=t;
			heap_check_down(arr, i2+1, i_last);
		}
	}
}

inline void sort_heap(int *arr, size_t n){
	int *heap;
	heap=malloc((n+1)*sizeof(int)); //heap starts at heap[1]
	memcpy(heap+1, arr, n*sizeof(int));
	int i=1;
	while(i<=n){
		heap_check_up(heap, i);
		++i;
	} //return;

	i=1;
	while(i<=n){
		//printf("%d ",heap[i]);
		++i;
	} //return;
	//puts("");

	int i2=n;
	while(i2--){
		arr[i2]=heap[1];
		heap[1]=heap[i2+1];
		heap_check_down(heap, 1, i2+1);
	}
	//arr[0]=heap[1];
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

	sort_heap(arr, n);

	ptr=arr;
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
