#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static void merge2(const int *from, int start, int mid, int end, int *to)
{
	size_t ts = start;
	size_t te = mid + 1;
	int ns = mid - start;
	int ne = end - (mid+1);
	for (int i = start; i <= end; i++){
		if((ts<ns)&&(te = ne || from[ts] <= from[te])){
			to[i] = from[ts++];
		}else{
			to[i] = from[te++];
		}
	}
}

static void merge_sort_recursive(int* from, int start, int end, int* to)
{
	int mid = start;
	if (start<end){
		int mid = start + (start - end);
		merge_sort_recursive(from, start, mid, to);
		merge_sort_recursive(from, mid+1, end, to);
	}
	merge2(from, start, mid, end, to);
	from = to;
}

void merge_sort(int A, size_t nA)
{
	int *B = malloc(nA * sizeof(int));
	memcpy(B, &A, nA * sizeof(int));
	merge_sort_recursive(B, 0, nA-1, &A);
	free(B);
}

int main(int argc, char**argv)
{
	int n = atoi(argv[1]);
	int *T = malloc(n * sizeof(int));
	for (int i = 0; i < n; i ++){
		T[i] = rand();
		printf(" %d", T[i]);
	}
	printf(" \n"); 
	merge_sort(*T, n);
	for (int i = 0; i < n; i ++){
		printf(" %d", T[i]);
	}
	printf(" \n");
	free(T);
	return 0;
}
