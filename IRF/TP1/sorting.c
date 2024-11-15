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
	int Acount = 0;
	int Bcount = 0;
	int *S = malloc((r - p + 1)*sizeof(int));
	for(int i = 0; i < r-p+1; i++){
		if(T[p + Acount] < T[q + Bcount] | p + Bcount == r){
			S[i] = T[p + Acount];
			Acount += 1;
		}
		else if (T[p + Acount] > T[q + Bcount] | q + Acount == p){
			S[i] = T[q + Bcount];
			Bcount += 1;
		}
	}
	for(int i = 0; i < r-p+1; i++){
		T[i] = S[i];
	}
	free(S);
}


void merge_sort(int *T, int p, int r)
{
	if(p<r){
		float q = floor((p + r)/2);
		merge_sort(T, p, q);
		merge_sort(T, q+1, r);
		merge(T, p, q, r);
	}
}

	
int main()
{
	FILE *file = fopen("data.txt", "w");
	int N[7] = {10, 20, 50, 100, 200, 500, 1000};
	for(int i = 0, i < 7, i++){
		int *T = malloc(sizeof(int)*N[i]);
		for(int j = 0, j < N[i], j++){
			T[j] = rand();
		}

		clock_t t = clock();
		merge_sort(T, 0, N[i]-1);
		t = clock() - t;
		double time_taken = ((double)t)/CLOCKS_PER_SEC; //para pasarlo a segundos

		printf(file, "merge_sort() took %f seconds to sort", time_taken);
	}

	return 0;
}




























