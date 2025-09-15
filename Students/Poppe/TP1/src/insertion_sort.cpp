#include <utility>

#include "insertion_sort.hpp"

void insertion_sort(int* array, size_t size) {
    for (size_t i = 1; i < size; ++i) {
        int current = array[i];
        size_t j = i;
        for(; j > 0; --j) {
            if(array[j - 1] > current) {
                array[j] = array[j - 1];
            } else {
                break;
            }
        }
        array[j] = current;
    }
}
