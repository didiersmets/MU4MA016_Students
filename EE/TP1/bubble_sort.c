#include <stdio.h>
#include <time.h>
#include <stdlib.h>
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

int main (int argc, char **argv)
{
	int n = atoi(argv[1]);
	int *T = malloc(n * sizeof(int));
	srand(time(NULL));
	for (int i = 0; i < n; i ++){
		T[i] = rand() % 100 + 1;
	}
	bubble (T, n);
	for (int i = 0; i < n; i ++){
		printf(" %d", T[i]);
	}
	printf(" \n");
	free(T);
	return 0;
}
