#include "mergesort.h"
#include <stdlib.h>

static void merge(size_t length, size_t mid, int *array) {
    int *temp = (int *)malloc(length * sizeof(int));
    size_t i = 0, j = mid, k = 0;

    while (i < mid && j < length) {
        if (array[i] <= array[j]) {
            temp[k++] = array[i++];
        }
        else {
            temp[k++] = array[j++];
        }
    }

    while (i < mid) {
        temp[k++] = array[i++];
    }

    while (j < length) {
        temp[k++] = array[j++];
    }

    // Copy the merged array back to the original array
    for (i = 0; i < length; i++) {
        array[i] = temp[i];
    }

    free(temp);
}

void merge_sort(int *array, size_t length) {
    if (length < 2) {
        return; // end of recursion
    }

    size_t mid = length / 2;

    // Recursively sort the two halves
    merge_sort(array, mid);
    merge_sort(array + mid, length - mid);

    // Merge the sorted halves
    merge(length, mid, array);
}
