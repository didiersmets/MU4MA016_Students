#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

void bubble_sort(int* loc, int size)
{
	for (int j = 1; j<size; j++){	
		for (int i=0; i<size - j; i++){
			if (loc[i] > loc[i+1]){
				int tmp = loc[i+1];
				loc[i+1] = loc[i];
				loc[i] = tmp;
			}
		}
	}
}

void insertion_sort(int* loc, int size)
{
	for(int i = 1; i < size; ++i){
		int j = i;
		while(j > 0 && loc[j] < loc[j-1]){
			int tmp = loc[j-1];
			loc[j] = loc[j-1];
			loc[j-1] = tmp;
			j--;
		}
	}
}


void merge(int* T, int p, int q, int r)
{
	int n1 = q - p + 1;
	int n2 = r - q;
	int* L = malloc(n1 * sizeof(int));
	int* R = malloc(n2 * sizeof(int));

	for (int i = 0; i < n1; i++) L[i] = T[p + i];
	for (int i = 0; i < n2; i++) R[i] = T[q + 1 + i];

	int i = 0, j = 0, k = p;
	while(i < n1 && j < n2){
		if(L[i] <= R[j]) {
			T[k] = L[i];
			i++;
		}
		else {
			T[k] = R[j];
			j++;
		}
		k++;
	}

	while(i < n1) T[k++] = L[i++];
	while(j < n2) T[k++] = R[j++];

	free(L);
	free(R);
}

void merge_sort(int* loc, int p, int r)
{
	if (p<r){
		int q = p + (r - p)/2;
		merge_sort(loc, p, q);
		merge_sort(loc, q+1, r);
		merge(loc, p, q, r);
	}
}

int main(){
	int lst[7] = {10, 20, 50, 100, 200, 500, 1000};
	double* times1 = malloc(7 * sizeof(double));
       	double* times2 = malloc(7 * sizeof(double));
	double* times3 = malloc(7 * sizeof(double));       
	for (int j = 0; j < 7; j++){
		int k = lst[j];
		int arr[k];
		srand(0);
		for (int i = 0; i < k; i ++){
			arr[i] = rand();
		}
		
		clock_t start = clock();
		
		bubble_sort(arr, k);

		clock_t end = clock();
		times1[j] = (double)(end - start) /  CLOCKS_PER_SEC;
	}

	for (int j = 0; j < 7; j++){
        	int k = lst[j];
		int arr[k];
                srand(0);
                for (int i = 0; i < k; i ++){
                        arr[i] = rand();
                }
                clock_t start = clock();

                insertion_sort(arr, k);

                clock_t end = clock();
                times2[j] = (double)(end - start) /  CLOCKS_PER_SEC;
        }

	for (int j = 0; j < 7; j++){
                int k = lst[j];
                int arr[k];
                srand(0);
                for (int i = 0; i < k; i ++){
                        arr[i] = rand();
                }
                clock_t start = clock();

                merge_sort(arr, 0, k-1);

                clock_t end = clock();
                times3[j] = (double)(end - start) /  CLOCKS_PER_SEC;
        }

	FILE *file = fopen("data.txt", "w");
	if (file == NULL){
		perror("Error opening file");
		return 1;
	}

	for (int k = 0; k < 7; k++){
		fprintf(file, "%.2d\t%.5f\n", lst[k], times1[k]);
	}
	fprintf(file, "\n");

	for (int k = 0; k < 7; k++){
                fprintf(file, "%.2d\t%.5f\n", lst[k], times2[k]);
        }
	fprintf(file, "\n");

	for (int k = 0; k < 7; k++){
                fprintf(file, "%.2d\t%.5f\n", lst[k], times3[k]);
        }
	fprintf(file, "\n");

	fclose(file);

	printf("Data written to data.txt\n");

	for (int k = 0; k < 7; k++){
		printf("The elapsed time is %lf seconds for sorting %d elements using bubble sort \n", times1[k], lst[k]);
	}
	free(times1);
	for (int k = 0; k < 7; k++){
                printf("The elapsed time is %lf seconds for sorting %d elements using insertion sort \n", times2[k], lst[k]);
	}
	 free(times2);
	 for (int k = 0; k < 7; k++){
                printf("The elapsed time is %lf seconds for sorting %d elements using merge sort \n", times3[k], lst[k]);
	}

	free(times3);
}
