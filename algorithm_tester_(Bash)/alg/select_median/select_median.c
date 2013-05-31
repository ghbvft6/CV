#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int cmps;

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

int median5(int *a, int i){
	sort_insert(a+i, 5);
	return a[i+2];	
}

int medianx(int *a, int first, int last){
	sort_insert(a+first, last-first);
	return a[(last-first+1)>>1];	
}

int partition(int *a, int last, int pivot){
	int first=0;
	int tmp;
	tmp=a[last];
	a[last]=a[pivot];
	a[pivot]=tmp;
	int i=first+1;
	while(i<last){
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
	a[last]=a[first];
	a[first]=tmp;
	return first;
}

int select_median(int *a, int n, int k){
	if(n<=5){
		sort_insert(a, n);
		return a[k];
	}
	int *medians;
	int medians_size=0;
	int block;
	medians=malloc((n+4)/5*sizeof(int)); 
	block=0;
	int block_lim;
	block_lim=n/5*5;
	while(block<block_lim){
		medians[medians_size++]=median5(a, block);
		block+=5;
	}
	int pivot;
printf("@%d\n",block);
	if(block<n){
		medians[medians_size++]=medianx(a, block, n);
		pivot=select_median(medians, medians_size, medians_size>>1);
		if(pivot==medians_size-1) pivot=n-5+((n%5)>>1);
		else pivot=pivot*5+2;
	} else pivot=select_median(medians, medians_size, medians_size>>1)*5+2;
//return 0;
	int pivot_real;
	pivot_real=partition(a, medians_size-1, pivot);
	//printf("A:%d B:%d\n",pivot,pivot_real);
	free(medians);
	if(k<=pivot_real) select_median(a, pivot_real+1, k);
	else select_median(a+pivot_real+1, n-pivot_real, k-pivot_real-1); 
}

int main(){
	srand(time(NULL));

	int k;


	cmps=0;
	int n, *ptr;
	scanf("%d", &n);
	scanf("%d", &k);

	int *arr=NULL;
	arr=malloc(n*sizeof(int));
	if(arr==NULL){ printf("out of memory"); return 0;}

	ptr=arr;
	int *ptr_lim=ptr+n;
	while(ptr!=ptr_lim){
		scanf("%d", ptr);
		++ptr;
	}

	
	ptr=arr;
	int ptrlim=ptr+n;
	while(ptr!=ptr_lim){
		printf("%d ", *ptr);
		++ptr;
	}
	printf("%d",select_median(arr, n, k));

	FILE *file;
	file = fopen("file.txt","w"); /* apend file (add text to
a file or create a file if it does not exist.*/
fprintf(file,"%d\n",cmps); /*writes*/
fclose(file); /*done!*/ 
return 0;
}
