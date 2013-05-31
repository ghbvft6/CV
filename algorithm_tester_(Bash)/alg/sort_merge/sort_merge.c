#include <stdio.h>
#include <stdlib.h>

//inline void cmp_int(const void *a, const void *b){
//	return *(const int*)a-*(const int*)b;
//}

unsigned int cmps;

inline void sort_merge(int **base, const size_t num){
	static int *arr;
	static int *arr_merged; //merge's output
	static int *tmp;
	static size_t block_size; //size of block
	static size_t i; //index of arr_merged
	arr=*base;
	arr_merged=malloc(num*sizeof(int));
	block_size=1;
	while(block_size<num){
		i=0;
		//memcpy(arr2,arr,num*sizeof(int));
		static size_t left; //index of left block in arr
		static size_t right; //index of right block in arr
		left=0;
		right=block_size;
//puts("");
		while(right<num){
			static size_t left_end; //end of left block
			static size_t right_end; //end of right block
			left_end=right;
			right_end=right+block_size;
if(right_end>num) right_end=num;
			while(left<left_end){
//printf("cmp: %u (%u) %u (%u) @", left,arr[left], right,arr[right]);
				++cmps; /* STATS */
				if(arr[left]>arr[right] && right<right_end){
					arr_merged[i]=arr[right];
					++right;
				} else{
					arr_merged[i]=arr[left];
					++left;
				}
//printf("merged: %u (%u)\n", i, arr_merged[i]);
				++i;
			}
//printf("right: %u\n", right_end);
			while(i<right_end){ //knowing that i==right
				arr_merged[i]=arr[i];
//printf("merged: %u (%u)\n", i, arr_merged[i]);
				++i;
			}
			left=right_end;
			right=right_end+block_size;
		}
	while(i<num){ //knowing that i==right
				arr_merged[i]=arr[i];
//printf("merged: %u (%u)\n", i, arr_merged[i]);
				++i;
			}		
		block_size<<=1;
		tmp=arr; //switch pointers instead of copying the array
		arr=arr_merged;
		arr_merged=tmp;
	int i=0;
	while(i<num){
		//printf("$%d ", arr[i]);
		++i;
	}
i=0;
//puts("");
while(i<num){
//		printf("$%d ", arr_merged[i]);
		++i;
	}
//puts("");
	}
	*base=arr;
	//free(arr_merged);
}

int main(){
	cmps=0;

	unsigned int n;
	unsigned int i;
	int *arr;
	scanf("%u", &n);   
	i=n;
	arr=malloc(n*sizeof(int));
	while(i--) scanf("%d", &arr[i]);
	sort_merge(&arr, n);
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
