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
	FILE *fptr = fopen("data.txt", "w");
	int N[] = {10,20,50,100,200,500,1000};
	for (int j = 0; j < 7; j ++){
		int *T = malloc(N[j] * sizeof(int));
		srand(time(NULL));
		for (int i = 0; i < N[j]; i ++){
			T[i] = rand() % 100 + 1;
		}
		clock_t begin = clock();
		merge_sort(T, N[j]);
		clock_t end = clock();
		double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
		fprintf(fptr, " %d", N[j]);
		fprintf(fptr, " %f", time_spent);
		fprintf(fptr," \n");
		printf(" %f", time_spent);
		free(T);
	}
	printf(" \n");
	fclose(fptr);
	return 0;
}
