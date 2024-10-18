#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>


void bubble_sort(int *A, int size)
{
        for(int i = 1, i<size, i++){
                for(int j = 0, j<size-i, j++){
                        if (A[j] > A[j+1]){
                                int tmp = A[j]; // int xq guardas un entero, lo llamo tmp de temporary
                                A[j] = A[j+1];
                                A[j+1] = tmp;
                        }
                }
        }
}


void insertion_sort(int *A, int size)
{
	for(int i, i<size; i++){
		int j = i;
		while(j>0 && A[j]<A[j-1]){
			float tmp = A[j-1]; // poner float y no int xq estas guardando una secuencia no un num
			A[j-1] = A[j];
			A[j] = tmp;
			j--;
		}
	}
}

void merge(int *T, int p, int q, int r)
{
	int *S = malloc((r - p + 1)







void merge_sort(int *T, int p, int r)
{
	if(p<r){
		float q = ((p + r)/2);
		merge_sort(T, p, q);
		merge_sort(T, q+1, r);
		merge(T, p, q, r);
	}
}

	












int main

