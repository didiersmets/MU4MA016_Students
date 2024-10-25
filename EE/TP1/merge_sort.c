#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

void merge(const int *from, int start, int mid, int end, int *to)
{
	size_t ts = start;
	size_t te = mid;
	int ns = mid - start;
	int ne = end - mid;
	for (int i = start; i < end; i++){
		if((ts < mid )&&(te == end || from[ts] <= from[te])){
			to[i] = from[ts ++];
		}else{
			to[i] = from[te ++];
		}
	}
}

void merge_sort_recursive(int* from, int start, int end, int* to)
{
	int mid = 0;
	if (start<end - 2){
		mid = (start + end)/2;
		merge_sort_recursive(to, start, mid, from);
		merge_sort_recursive(to, mid, end, from);
	}else{
		mid = end-1;
	}
	merge(from, start, mid, end, to);
}

void merge_sort(int *A, size_t nA)
{
	int *B = malloc(nA * sizeof(int));
	memcpy(B, A, nA * sizeof(int));
	merge_sort_recursive(B, 0, nA, A);
	free(B);
}

int main(int argc, char**argv)
{
	int N[7];
	N[0] = 10;
	N[1] = 20;
	N[3] = 50;
	N[4] = 100;
	N[5] = 500;
	N[6] = 1000;
	for (int n = 0; n < 7; n ++){
		int *T = malloc(N[n] * sizeof(int));
		srand(time(NULL));
		for (int i = 0; i < n; i ++){
			T[i] = rand() % 100 + 1;
			printf(" %d", T[i]);
		}
		printf(" \n");
		clock_t begin = clock();
		merge_sort(T, n);
		clock_t end = clock();
		double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
		printf( );
	}
	return 0;
}
