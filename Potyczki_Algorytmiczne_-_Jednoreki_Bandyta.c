#include <stdlib.h>

unsigned int first_row[300001], first_row_inv[300001];
unsigned int row[2][300001], matching_shift[300001][2];

int llu_cmp(const void *a, const void *b){
	//return *(unsigned long long *)a-*(unsigned long long *)b;
	return *(unsigned long long *)a<*(unsigned long long *)b ? -1:(*(unsigned long long *)a==*(unsigned long long *)b ? 0:1);
}

int main(){
	//unsigned int *first_row, *first_row_inv;
	//unsigned int *row[2], (*matching_shift)[2];
	unsigned long long *matching_shift_ptr_ll; //assume: unsigned int[2] == unsigned long long[1]
	unsigned int match_len, match_len_max;
	int n, i;

	//first_row = malloc(300001*sizeof(unsigned int));
	//first_row_inv = malloc(300001*sizeof(unsigned int));
	//row[0] = malloc(300001*sizeof(unsigned int));
	//row[1] = malloc(300001*sizeof(unsigned int));
	//matching_shift = malloc(300001*sizeof(unsigned int [2]));

	scanf("%u", &n);
	i = 1;
	while(i<=n){
		scanf("%u", &first_row[i]);
		++i;
	}
	i = 1;
	while(i<=n){
		scanf("%u", &row[0][i]);
		++i;
	}
	i = 1;
	while(i<=n){
		scanf("%u", &row[1][i]);
		++i;
	}

	//invert first row
	i = n;
	while(i>0){
		first_row_inv[first_row[i]] = i;
		--i;
	}
	
	//check 2nd row
	i = n;
	while(i>0){
		matching_shift[row[0][i]][0] = (n+first_row_inv[row[0][i]]-i)%n;
		--i;
	}
	//check 3rd row
	i = n;
	while(i>0){
		matching_shift[row[1][i]][1] = (n+first_row_inv[row[1][i]]-i)%n;
		--i;
	}

	//sort matching pairs
	qsort(&matching_shift[1], n, sizeof(unsigned long long), llu_cmp); //assume: unsigned int [2] == unsigned long long

	//find largest amout of same pairs
	matching_shift_ptr_ll = (unsigned long long *)matching_shift;
	match_len = match_len_max = 1;
	i = n-1;
	while(i>0){
		if(matching_shift_ptr_ll[i]==matching_shift_ptr_ll[i+1]) ++match_len;
		else{
			if(match_len>match_len_max) match_len_max = match_len;
			match_len = 1;
		}
		--i;
	}
	if(match_len>match_len_max)match_len_max = match_len;

	printf("%u", match_len_max);

	return 0;
}
