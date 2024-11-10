#include "sorting.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void bubble_sort(int* arr, int n) {
	for (int j = 0; j < n; j++) {
		for (int i = 1; i < n; i++) {
			if (arr[i] < arr[i - 1]) {
				int temp = arr[i];
				arr[i] = arr[i - 1];
				arr[i - 1] = temp;
			}
		}
	}
}

void insertion_sort(int* arr, int n) {
	for (int i = 1; i < n + 1; i++) {
		for (int j = i; j > 0; j--) {
			if (arr[j] < arr[j - 1]) {
				int temp = arr[j];
				arr[j] = arr[j - 1];
				arr[j - 1] = temp;
			}
		}
	}
}
/*
void merge(int* T, int* S, int p, int q, int r) {
	int i = 0;
	int j = 0;
	while ((p + i < r - q) || (q + j < r)) {
		printf("(i, j): %d, %d \n", i, j);
		printf("%d, %d \n", T[p + i], T[q + j]);
		if (T[p + i] < T[q + j]) {
			S[p] = T[p];
			i++;
		} else {
			S[p] = T[q];
			j++;
		}
	}
}*/

void merge(int* T, int* S, int p, int q, int r) {
	int i = 0;
	int j = 0;
	int k = 0;
	while (p + i < r - q && q + j < r) {
		if (T[p + i] <= T[q + j]) {
			S[k] = T[p + i];
			i++;
		} else {
			S[k] = T[q + j];
			j++;
		}
		k++;
	}
	while (p + i < r - q) {
		S[k] = T[p + i];
		i++;
		k++;
	}
	while (q + j < r) {
		S[k] = T[q + j];
		j++;
		k++;
	}
}

/*
// Non-recursive merge sort
void merge_sort(int* arr, int n) {
	while () {
		int
	}
}
*/

void merge_sort_recursive(int* T, int* S, int p, int r) {
	if (p < r) {
		int q = (p + r) / 2;
		printf("p:%d \n", p);
		printf("q:%d \n", q);
		printf("r:%d \n", r);
		merge_sort_recursive(T, S, p, q);
		merge_sort_recursive(T, S, q + 1, r);
		merge(T, S, p, q, r);
		printf("\n\n");
	}
}

// Recursive merge sort
void merge_sort(int* arr, int n) {
	int* S = malloc(n * sizeof(int));
	for (int i = 0; i < n; i++) memcpy(S + i, arr + i, sizeof(int));
	merge_sort_recursive(arr, S, 0, n - 1);
	for (int i = 0; i < n; i++) memcpy(arr + i, S + i, sizeof(int));
	free(S);
}

