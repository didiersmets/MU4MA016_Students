#include <stdio.h>
#include <stdlib.h>

#include "sorting.h"

int main(int argc, char *argv[]) {
	int n = 10;
	int *T = malloc(n * sizeof(int));
	for (int i = 0; i < n; i++) {
		T[i] = 10 - i;
	}
	// printf("Starting Bubble Sort");
	// bubble_sort(T, n);
	// printf("Starting insertion sort...");
	// insertion_sort(T, n);

	// int *S = malloc(n * sizeof(int));
	// merge(T, S, 0, 4, 9);
	// for (int i = 0; i < n; i++) printf("%d \n", S[i]);

	printf("Starting merge sort... \n");
	merge_sort(T, n);
	printf("Printing result:\n");
	for (int i = 0; i < n; i++) printf("%d \n", T[i]);
	free(T);
}
