#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {

	int n = atoi(argv[1]);
	
	int size = n*(n-1)/2;

	int* A = (int*) malloc(size*sizeof(int));

	for(int i = 0; i < n; ++i) {

		int B[i+1];
		B[0] = 1;
		B[i] = 1;

		for(int j = 1; j < i; ++j) {
			B[j] = A[j-1]+A[j];
		}

		for(int j = 0; j < sizeof(B)/sizeof(int); ++j) {
			printf("%d", B[j]);
			A[j] = B[j];
		}
	}
	 	            	
	return 0;
}
