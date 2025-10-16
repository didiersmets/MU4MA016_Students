#include "bubblesort.h"
#include <stdbool.h>

void bubblesort(int *array, size_t length) {
    bool swapped;
    for (size_t i = 0; i < length - 1; i++) {
        swapped = false;
        for (size_t j = 0; j < length - i - 1; j++) {
            if (array[j] > array[j + 1]) {
                // Swap array[j] and array[j + 1]
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
                swapped = true;
            }
        }
        // If no two elements were swapped in the inner loop, then the array is sorted
        if (!swapped) {
            break;
        }
    }
}