#include <utility>
#include <string>

#include "merge_sort.hpp"
#include "insertion_sort.hpp"

const size_t MERGE_SORT_THRESHOLD = 32;

void merge_sort(int* array, size_t size) {
    int* temp = new int[size];
    int* from = array;
    int* into = temp;
    for(size_t l=0; l < size; l += MERGE_SORT_THRESHOLD) {
        size_t len = std::min(MERGE_SORT_THRESHOLD, size - l);
        insertion_sort(array + l, len);
    }
    for(size_t width = MERGE_SORT_THRESHOLD; width < size; width*=2) {
        for(size_t l=0; l < size; l += width * 2) {
            size_t l_len = std::min(width, size - l);
            size_t l_i = 0;
            size_t r = l + width;
            size_t r_i = 0;
            if (r < size) {
                size_t r_len = std::min(width, size - r);
                while(l_i < l_len && r_i < r_len) {
                    if(from[l + l_i] < from[r + r_i]) {
                        into[l + l_i + r_i] = from[l + l_i];
                        l_i++;
                    } else {
                        into[l + l_i + r_i] = from[r + r_i];
                        r_i++;
                    }
                }
                while(r_i < r_len) {
                    into[l + l_i + r_i] = from[r + r_i];
                    r_i++;
                }
            }
            while(l_i < l_len) {
                into[l + l_i + r_i] = from[l + l_i];
                l_i++;
            }
        }
        std::swap(from, into);
    }
    if (from == temp) {
        //memcopy back since odd transfer count
        memcpy(array, temp, size * sizeof(int));
    }
    delete[] temp;
}

void merge(int* array, size_t l, size_t l_end, size_t r, size_t r_end, int* output) {
    while(l < l_end && r < r_end) {
        if(array[l] < array[r]) {
            std::swap(*output, array[l]);
            l++;
            output++;
        } else {
            std::swap(*output, array[r]);
            r++;
            output++;
        }
    }
    while(l < l_end) {
        std::swap(*output, array[l]);
        l++;
        output++;
    }
    if(array + r == output) {
        return;
    }
    while(r < r_end) {
        std::swap(*output, array[r]);
        r++;
        output++;
    }
}

void merge_sort_inplace(int* array, size_t size) {
    if (size <= MERGE_SORT_THRESHOLD) {
        insertion_sort(array, size);
        return;
    }
    size_t sorted = size;

    while (sorted > 1) {
        size_t halved = sorted / 2;
        size_t quarter = halved / 2;
        merge_sort_inplace(array + halved, quarter);
        merge_sort_inplace(array + halved + quarter, halved - quarter);
        merge(array + halved, 0, quarter, quarter, halved, array);

        merge(array, 0, halved, sorted, size, array + sorted - halved);
        sorted -= halved;
    }
    for (size_t i = 0; i < size - 1; i++) {
        if (array[i] > array[i + 1]) {
            std::swap(array[i], array[i + 1]);
        } else {
            break;
        }
    }
}
