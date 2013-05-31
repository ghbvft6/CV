int n,N,M;
int T=0;
int i,j;
int row_max;

inline void algorithm(){
	scanf("%d %d", &N, &M);
	int arr[N][M];
	int columns_maxs[M];
	i = 0;
	while(i<N){
		j = 0;
		while(j<M){
			scanf("%d", &arr[i][j]);
			++j;
		}
		++i;
	}

	//get maxs of columns
	j = 0;
	while(j<M){
		columns_maxs[j] = arr[0][j];
		i = 1;
		while(i<N){
			if(columns_maxs[j]<arr[i][j]) columns_maxs[j] = arr[i][j];
			++i;
		}
		++j;
	}

	i = 0;
	while(i<N){
		//get max of row
		row_max = arr[i][0];
		j=1;
		while(j<M){
			if(row_max<arr[i][j]) row_max=arr[i][j];
			++j;
		}
		//for every lower square check if it can be done vertically
		j = 0;
		while(j<M){
			if(arr[i][j]!=row_max && arr[i][j]<columns_maxs[j]){
				printf("Case #%d: NO\n", T);
				return;
			}
			++j;
		}
		++i;
	}

	printf("Case #%d: YES\n", T);
}

int main(){
	scanf("%d",&n);

	while(++T<=n){
		algorithm();		
	}

	return 0;
}

