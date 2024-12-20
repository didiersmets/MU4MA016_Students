#include <stdio.h>
#include <stdlib.h>

void matrix_product1(float C[], const float A[], const float B[], int N){
	for (int i = 0; i < N; ++i){
		for(int j = 0; j < N; j++){
			/* Compute C_{i, j} */
			C[i*N + j] = 0;
			for (int k = 0; k < N; k++){
				C[i*N + j] += A[i*N + k] * B[b*N + j];
			}
		}
	}
}

void matrix_product2(float C[], const float A[], const float B[], int N){
	for (int i=0; i<N; ++i){
		/* Zero initialize C */
		for (int j = 0; j<N; j++){
			C[i*N + j] = 0;
		}
		for (int k = 0; k<N; k++){
			for (int j = 0; j<N; j++){
				/* Update C_{i,j} */
				C[i*N + j] += A[i*N + k] * B[k*N + j];
			}
		}
	}
}
