#include <stdio.h>
#include <time.h>

void bubble(int *B, int size_A)
{
	int temp = 0;
	for (int j = 0; j<size_A; j++){
		int i = 0;
		while (i < size_A-j){
			if (B[i] > B[i+1]){
				temp = B[i];
				B[i] = B[i+1];
				B[i+1] = temp;
			}else{
				i++;
			}
		}
	}
}

int main(int argc, char**ardv)
{
	int N = {10, 20, 50, 100, 200, 500, 1000};
	for (int i = 0; i<7; i++){
		void n = N[i];
		int T=malloc(n*size(int));
		for (i=0; i<n; i++){
			T[i] = rand();
		}
		clock_t start,end;
		t = clock();
		bubble(T, n);
		t = clock() - t;
		double time_taken = ((double)t)/CLOCKS_PER_SEC;
		free(T);
	}
	return 0;
}

