#include <stddef.h>

void merge(int *C,const int *A, size_t nA,const int *B, size_t nB)
{
	size_t nC = nA+nB;
	size_t tA = 0;
	size_t tB = 0;
	for (size_t k=0; k<nC; k++){
		if((tA<nA)&&(tB = nB || A[tA]<=B[tB])){
				C[k] = A[tA++];
		}else{
			C[k] = B[tB++];
		}
	}			
}

static void merge_sort_recursive(int From, int start, int end, int To)
{
	for (n = start; n < end; n++){
	}
}




void merge_sort(int A, size_t nA)
{
	int *B = malloc(nA * sizeof(int));
	memcpy(B, A, nA * sizeof(int));
	merge_sort_recursive(B, 0, nA, A);
	free(B);
}


