int main(){
	char s[500001];
	int i,n=0;
	//gets(s);
	scanf("%d\n", &i);
	i-=2;
	gets(s);
	//i = strlen(s)-2;
	while(i>=0){
		if(s[i]==s[i+1]) ++n, i-=2;
		else --i;
	}
	printf("%d",n);
	return 0;
}
