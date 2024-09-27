#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sorting.h"

int main() {
    // int T[] = {6, 7, 11, 23, 2, 3, 9, 20};
    // int len = sizeof(T) / sizeof(T[0]);
    //
    // merge_sort(T, 0, len - 1);
    //
    // for (int i = 0; i < len; i++) {
    //     printf("T[%i] = %i\n", i, T[i]);
    // }
  int N[] = {10, 20, 50, 100, 200, 500, 1000};

  for (int i = 0; i < 7; i++) {
    int n = N[i];
    int arr1[n];
    int arr2[n];
    int arr3[n];
    for (int j = 0; j < n; j++) {
      int random = rand() % 100;
      arr1[j] = random;
      arr2[j] = random;
      arr3[j] = random;
    }

    clock_t start, end;
    double cpu_time_used;

    start = clock();
    bubble_sort(arr2, n); 
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("bubble_sort with %d elements took %f seconds\n", n, cpu_time_used);

    start = clock();
    insertion_sort(arr3, n); 
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("insertion_sort with %d elements took %f seconds\n", n, cpu_time_used);

    start = clock();
    merge_sort(arr1, 0, n - 1);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("merge_sort with %d elements took %f seconds\n\n", n, cpu_time_used);
  }
    
  return 0;
}
