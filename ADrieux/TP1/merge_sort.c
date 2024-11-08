#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

void merge(int *T, int p, int q, int r)
{
	int n1 = q-p+1;
	int n2 = r-q;
	int *L = (int *)malloc(n1*sizeof(int));
	int *R = (int *)malloc(n2*sizeof(int));
	for (int i = 0; i<n1; i++)
	{
		L[i] = T[p+i];
	}
	for (int j = 0; j<n2; j++)
	{
		R[j] = T[q+j+1];
	}
	int index_L = 0;
	int index_R = 0;
	for (int k=p; k<r-p+1; k++)
	{
		if ((index_L < n1)&&((index_R == n2) || L[index_L] <= R[index_R]))
		{
			T[k] = L[index_L];
			index_L = index_L  + 1;
		} else {
			T[k] = R[index_R];
			index_R = index_R + 1;
		}
	}
	free(L);
	free(R);
}

void merge_sort(int *T, int p, int r)
{
	if (p > r)
	{
		return;
	}
	else if (p < r)
	{
		int q = floor((p+r)/2);
		merge_sort(T, p, q);
		merge_sort(T, q+1, r);
		merge(T, p, q, r);
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
	N[7] = 1000000;
	srand(time(NULL));
	for (int i = 0; i<8; i++)
	{
		int *T = (int *)malloc(N[i]*sizeof(int));
		for (int j = 0; j < N[i]; j++)
		{ 
			T[j] = rand();
		}
		clock_t begin = clock();
		merge_sort(T, 0, N[i] - 1);
		clock_t end = clock();
		unsigned long time_spent = (end - begin)*1000/CLOCKS_PER_SEC;
		printf("merge_sort : %ld ms\n", time_spent);
		free(T);
	}
	return 0;
}





	