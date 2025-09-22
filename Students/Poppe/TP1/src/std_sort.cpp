#include <utility>

#include "std_sort.hpp"
#include <algorithm> // for std::sort

void std_sort(int* array, size_t size) {
    std::sort(array, array + size);
}
