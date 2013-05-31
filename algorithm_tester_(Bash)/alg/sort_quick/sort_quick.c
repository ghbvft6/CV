#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//inline void cmp_int(const void *a, const void *b){
//	return *(const int*)a-*(const int*)b;
//}

unsigned int cmps;

int split_arr(int *arr, const int last){
	int *arr_tmp;
	int left;
	int right;
	int i;
	int mid;
	int pivot;
	arr_tmp=malloc((last+1)*sizeof(int));
	i=0;
	mid=last>>1;
	pivot=arr[mid];
	right=last;
	left=0;
//printf("%d %d %d\n",i,mid,pivot);
	while(i<mid){ //check arr to the pivot upward
		++cmps;
		if(arr[i]<pivot){
			arr_tmp[left]=arr[i];
			++left;
			
		} else{
			arr_tmp[right]=arr[i];
			--right;
		}
		++i;		
	}
	i=last;
//printf("%d %d\n",i,arr[i]);
	while(i>mid){ //check arr to the pivot downward
		++cmps;
		if(arr[i]<pivot){
			arr_tmp[left]=arr[i];
			++left;
			
		} else{
			arr_tmp[right]=arr[i];
			--right;
		}
		--i;		
	}

	arr_tmp[left]=pivot; //at this point left==right but mid!=left -> mid!=right
//printf("%d %d %d %d %d %d %d\n",arr_tmp[left],pivot,left,right,last,arr[0],arr[1]);
	memcpy(arr, arr_tmp, (last+1)*sizeof(int));
//printf("%d %d %d\n",last,arr_tmp[0],arr_tmp[4]);
	free(arr_tmp);
//return 0;
	return left;
}

inline void sort_quick(int *arr, int last){
	if(last>=1){
		int i;
		i=split_arr(arr, last);
//printf("%d\n",i);
//return
		sort_quick(arr, i);
//return
		sort_quick(arr+i+1, last-i-1);
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
	i=0;
	while(i<n){
		scanf("%d", &arr[i]);
		++i;
	}
	sort_quick(arr, n-1);
	i=0;
	while(i<n){
		printf("%d ", arr[i]);
		++i;
	}

	FILE *file;
	file = fopen("file.txt","w"); /* apend file (add text to
a file or create a file if it does not exist.*/
fprintf(file,"%d\n",cmps); /*writes*/
fclose(file); /*done!*/ 
	return 0;
}
