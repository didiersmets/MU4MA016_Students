#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>

void bubble_sort(int *A, int size)
{
	for(int i = 1, i<size, i++){
		for(int j = 0, j<size-i, j++){
			if (A[j] > A[j+1]){
				int tmp = A[j];
				A[j] = A[j+1];
				A[j+1] = tmp;
			}
		}
	}
}

int main



