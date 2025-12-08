// question 2.2 Insertion sort (2)
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void insertion_sort_swap(int *arr, int n) {
    for (int i = 1; i < n; i++) {
        int j = i;
        while (j > 0 && arr[j - 1] > arr[j]) {
            int t = arr[j - 1];
            arr[j - 1] = arr[j];
            arr[j] = t;
            j--;
        }
    }
}
