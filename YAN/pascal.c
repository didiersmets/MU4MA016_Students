#include <stdio.h>
#include <stdlib.h>

int main( int argc , char **argv){
	int n = atoi(argv[1]);
	if (n==0){return 0;}
	int *pascal = malloc(n*sizeof(int));
	pascal[0]=1;
	printf("line 1 : 1 \n");
	for(int i=1;i<n;i++){
		pascal[i]=1;
		printf("line %d: 1 ",i+1);
		for(int j=i-1; j>1;j--){
			pascal[j]+=pascal[j-1];
			printf("%d ",pascal[j]);
		}
		printf("1 \n");
	}
	return 0;
}

