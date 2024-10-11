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
			float tmp = loc[j-1];
			loc[j] = loc[j-1];
			loc[j-1] = tmp;
			j--;
		}
	}
}


void merge(int* T, int p, int q, int r)
{
	int A_count = 0;
	int B_count = 0;

	int* arr = malloc(r-p);

	for(int i = 0; i < r-p; i++){
		if(T[p + A_count] < T[q + B_count] | p + B_count == r){
			arr[i] = T[p + A_count];
			A_count += 1;
		}	
		else if (T[p + A_count] > T[q + B_count] | q + A_count == p){
			arr[i] = T[q + B_count];
                        B_count += 1;
		}
	}

	for(int i = 0; i < r-p; i++){
		T[i] = arr[i];
	}
}

void merge_sort(int* loc, int p, int r)
{
	if (p<r){
		float q = floor((p + r)/2);
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
		double time1 = (double) clock();
		time1 = time1 / CLOCKS_PER_SEC;
		
		bubble_sort(arr, k);

		double timedif = ( ((double) clock()) / CLOCKS_PER_SEC) - time1;
		times1[j] = timedif;
	}

	for (int j = 0; j < 7; j++){
        	int k = lst[j];
		int arr[k];
                srand(0);
                for (int i = 0; i < k; i ++){
                        arr[i] = rand();
                }
                double time2 = (double) clock();
                time2 = time2 / CLOCKS_PER_SEC;

                insertion_sort(arr, k);

                double timedif = ( ((double) clock()) / CLOCKS_PER_SEC) - time2;
                times2[j] = timedif;
        }

	for (int j = 0; j < 7; j++){
                int k = lst[j];
                int arr[k];
                srand(0);
                for (int i = 0; i < k; i ++){
                        arr[i] = rand();
                }
                double time3 = (double) clock();
                time3 = time3 / CLOCKS_PER_SEC;

                merge_sort(arr, 0, k);

                double timedif = ( ((double) clock()) / CLOCKS_PER_SEC) - time3;
                times3[j] = timedif;
        }

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
