#include <stdlib.h>

unsigned int side1[1000001], side1_size;
unsigned int side2[1000001], side2_size;

unsigned long long result;

int u_cmp(const void *a, const void *b){
	return *(unsigned int *)a-*(unsigned int *)b;
}

int main(){
	int i, j;

	scanf("%u%u", &side1_size, &side2_size);
	i = side1_size;
	while(i>0){
		--i;
		scanf("%u", &side1[i]);
	}
	i = side2_size;
	while(i>0){
		--i;
		scanf("%u", &side2[i]);
	}

	//we can sort it to make height checking synchronous (improvement from O(n*m) to O(n+m) in checking part)
	qsort(side1, side1_size, sizeof(unsigned int), u_cmp);
	qsort(side2, side2_size, sizeof(unsigned int), u_cmp);

	//check heights
	if(side1[side1_size-1]!=side2[side2_size-1]){
		printf("NIE");
		return 0;
	}
	side1[side1_size] = 2000000; //set guards
	side2[side2_size] = 2000001;
	result = 0;
	i = j = 0;
	while(i<side1_size && j<side2_size){
		while(side1[i]<side2[j]){
			result += (unsigned long long)side1[i]*(side2_size-j);
			++i;
		}
		while(side2[j]<=side1[i]){
			result += (unsigned long long)side2[j]*(side1_size-i);
			++j;
		}
	}

	printf("%llu", result);

	return 0;
}
