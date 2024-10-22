#include <stdlib.h>
#include <stdio.h>

void insertion_sort(int *A, int size)
{ 
	for (int i = 1; i < size; i++)
	{
		int j = i;
		while (j>0 && A[j-1] > A[j])
		{
			int tmp = A[j];
			A[j] = A[j-1];
			A[j-1] = tmp;
			j = j-1;
		}
	}
}

int main(int argc, char** argv)
{
	int N = atoi(argv[1]);
	int *A = (int *)malloc(N*sizeof(int));
	for (int i = 0; i<N; i++)
	{
		A[i] = rand();
	}
	insertion_sort(A,N);
	for (int i = 0; i<N; i++)
	{
		printf("%d", A[i]);
	}
	printf("\n");
}

