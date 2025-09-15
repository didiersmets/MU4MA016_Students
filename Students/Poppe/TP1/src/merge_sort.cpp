#include <utility>
#include <string>

#include "merge_sort.hpp"

void merge_sort(int* array, size_t size) {
    int* temp = new int[size];
    int* from = array;
    int* into = temp;
    for(size_t width = 1; width < size; width*=2) {
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
    if (into == from) {
        //memcopy back since odd transfer count
        memcpy(array, temp, size * sizeof(int));
    }
}
