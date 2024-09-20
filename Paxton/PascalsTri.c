#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){
	int n = atoi(argv[1]);
	if (n<=0){return 0;};
	
	int *triangle=malloc(n*sizeof(int));

	triangle[0]=1;
	printf("%d\n", triangle[0]);
	for (int line=1; line<n+1; line++){
		triangle[line]=1;
		for (int i=line-1; i>0; i--){
			triangle[i]+=triangle[i-1];
		}
		for (int j=0; j<line+1;j++){
			printf("%d ", triangle[j]);
			
		}
		printf("\n");
	}
	return 0;
}
