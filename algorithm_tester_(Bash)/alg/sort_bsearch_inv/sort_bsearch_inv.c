#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cmps;

/*int cmp_int(const void *a, const void *b){
	++cmps;
	return (*(int*)a-*(int*)b);
}*/

inline int *bsearch_inv(const int key, const int *base, const size_t num){
	static int first;
	static int last;
	static int mid;
	first=0;
	last=num-1;
	while(first<=last){ // @prevent while from rolling over with -1 by size_t
		mid=(first+last)>>1;
		/*if(key>base[mid]) first = mid+1, ++cmps; // key > mid
		else if(key<base[mid]) last = mid-1, ++cmps; // key < mid
		else return (int*)base+mid+1; // the same key found at mid*/
		++cmps;
		if(key>base[mid]) first=mid+1; // key > mid
		else last=mid-1; // key < mid
		//else return (int*)base+mid+1; // the same key found at mid
	}
	/* binary search didn't found the key */
	//return (int*)base+first;
	return (int*)base+first;
}

inline void sort_bsearch_inv(int *arr, size_t num){
	static int *arr_tmp;
	static int *arr_tmp_first;
	arr_tmp=malloc(num*sizeof(int));
	arr_tmp[num-1]=arr[0];
	static int *ptr;
	arr_tmp_first=arr_tmp+num-1;
	int i=1;
	while(i<num){
		ptr=bsearch_inv(arr[i],arr_tmp_first,i);
//printf("@%d %d %d,%d,%d\n",arr[i],ptr,arr_tmp_first,i, ptr-arr_tmp_first);

		memmove(arr_tmp_first-1, arr_tmp_first, (ptr-arr_tmp_first)*sizeof(int));
		*(ptr-1)=arr[i];
		--arr_tmp_first;
		++i;
//int j=i;
//while(j--) printf("%d ",arr_tmp_first[j]);
//puts(""); 
	}
	memcpy(arr, arr_tmp, num*sizeof(int));
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

	sort_bsearch_inv(arr, n);

	ptr=arr;
	ptr_lim=ptr+n;
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
