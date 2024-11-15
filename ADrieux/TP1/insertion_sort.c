#include <stdlib.h>
#include <stdio.h>
#include <time.h>

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
	int N[8];
	N[0] = 10;
	N[1] = 20;
	N[2] = 50;
	N[3] = 100;
	N[4] = 200;
	N[5] = 500;
	N[6] = 1000;
	N[7] = 10000;
	srand(time(NULL));
	for (int i=0;i<8;i++)
	{
		int *A = (int *)malloc(N[i]*sizeof(int));
		for (int j = 0; j<N[i];j++)
		{
			A[j] = rand();
		}
		clock_t begin = clock();
		insertion_sort(A,N[i]);
		clock_t end = clock();
		unsigned long time_spent = (end - begin)*1000/CLOCKS_PER_SEC;
		printf("insertion_sort : %ld ms\n", time_spent);
		free(A);
	}
	return 0;

}

