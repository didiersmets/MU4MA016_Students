#include <stdlib.h>
#include <stdio.h>

float *triangle_Pascal(int N) {
        float *A =(float *)malloc(N*N*sizeof(float));
  	for (int i=0; i < N; i++) {
		for (int j = 0; j < N; j++) {
		  if (i == j ) {
		    A[i * N + j] = 1;
		  } 
		  else if (j == 0) {
			  A[i * N + j] = 1;
		  }
		  else if (0 < j && j < i) {
		    A[i * N + j] = A[(i-1) * N + (j-1)] + A[(i-1) * N + j];
		  } 
		  else {
		    A[i * N + j] = 0;
		  }
		}
	}
	return(A);
}

int main(int argc, char** argv)
{
	int N = atoi(argv[1]);
	float *A = triangle_Pascal(N);
	/* Imprimer */
	for (int i=0; i<N; i++) {
		for (int j = 0; j<=i; j++) {
			printf(" %f", A[i*N+j]);
		}
		printf("\n");
	} 
	return 0;
}



