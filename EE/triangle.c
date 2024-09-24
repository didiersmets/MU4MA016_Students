#include <stdlib.h>

int *triangle(int n){
	int *A = malloc(n*n*sizeof(int));
	int i, j;
	for (i = 0; i<n; i++){
		for(j = 0; j<n; j++){
			if (0<j<i)
				A[i*n+j]=A[(i-1)*n+(j-1)]+A[(i-1)*n+j];
			else
				A[i*n+j]=1;
		}
	}
	return A;
}

int main(int argc, char** argv)
{
	int n = atoi(argv[1]);
	int *A = triangle(n);
	/* Imprimer */

	return 0;
}
