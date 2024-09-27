#include <stdlib.h>
#include <stdio.h>

int *triangle(int n)
{
	int *A = (int *)malloc(n*n*sizeof(int));
	for (int i = 0; i<n; i++){
		for(int j = 0; j<n; j++){
			if (0<j && j<i){
				A[i*n+j]=A[(i-1)*n+(j-1)]+A[(i-1)*n+j];
			}
			else{
				A[i*n+j]=1;
			}
		}
	}
	return A;
}

int main(int argc, char** argv)
{
	int n = atoi(argv[1]);
	int *A = triangle(n);
	/* Imprimer */
	for (int i = 0; i<n; i++){
		for (int j = 0; j<=i; j++){
			printf(" %d",A[i*n+j]);
		}
		printf(" \n");
	}
	return 0;
}
