#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
	int n = atol(argv[1]);
	int P[n][n+1] = {};
	printf("[");
	P[0][0] = 1;
	printf("%d", P[0][0]);

	int i = 1;
	for (i=1; i<=n; i++){
		printf("\n");

		P[i][0] = 1;
		P[i][i] = 1;
		printf("%d ", P[i][0]);

		int j=1;
		for (j=1; j<i; j++){
			P[i][j]=P[i-1][j] + P[i-1][j-1];
			printf("%d ", P[i][j]);
		}
		printf("%d ", P[i][i]);

	}
	printf("] \n");
	return 0;
}