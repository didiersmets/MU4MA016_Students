#include "insertionsort.h"
#include <stdio.h>

void insertionsort(int *array, size_t length) {
    for (size_t i = 1; i < length; i++) {

        // sort the element into the sorted sequence array[0..i-1]
        // stop swapping when the element isn't smaller than the one below it
        for (size_t j = i; j > 0 && array[j] < array[j - 1]; j--) {
            int temp = array[j];
            array[j] = array[j - 1];
            array[j - 1] = temp;
        }
    }
}