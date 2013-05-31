#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
	int n, r;
	scanf("%d", &n);
	
	printf("%d ", n);
	srand(time(NULL));
	printf("%d ", rand()%n);
	while(n--){
		r=rand()%10000000+1;
		printf("%d ", r);
	}
return 0;
}
