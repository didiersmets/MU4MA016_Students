#include <stdlib.h>
#include <stdio.h>

void bubble_sort(int *A, int size) 
{
	for (int i = 0; i < size; i++)
	{       
		int j = 0;
		while (j<size-i)
		{
			if (A[j] > A[j+1])
			{
				int tmp = A[j+1];
				A[j+1] = A[j];
				A[j] = tmp;
			}
			j = j + 1;
		}
	}
}

int main(int argc, char** argv)
{
	int N = atoi(argv[1]);
	int *A =(int *)malloc(N*sizeof(int));
	for (int i = 0; i<N; i++)
	{
		A[i] = rand();
	}
	bubble_sort(A, N);
	for (int i =0; i<N; i++)
	{
		printf("%d",A[i]);
	}
	printf("\n");
}



