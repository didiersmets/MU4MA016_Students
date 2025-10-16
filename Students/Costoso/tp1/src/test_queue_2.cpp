#include "circular_buffer_queue_2.h"
#include <cstdlib>
#include <iostream>
#include <algorithm>

void Bubble_sort(int* q, int lenght) {
    for (int i = 0; i < lenght; i++) {
        for (int j = i + 1; i < lenght; j++) {
            if (*(q + i) > *(q + j)) { std::swap(*(q + i), *(q + j)); }
        }
    }
}

void Insertion_sort(int* q, int lenght, int k) {
    for (int i = k + 1; i < lenght; i++) {
        for (int j = 0; j < k; j++) {
            if (*(q + i - 1 - j) > *(q + i - j)) {
                std::swap(*(q + i - 1 - j), *(q + i - j));
            }
        }
    }
}

template<typename T>
void Merge(int* L, int p, int q, int r) {
    int i = p;
    int j = q+1;
    Queue<T>* Sorted = queue_init<T>(sizeof(int), r);
    while (i != q+1 || j != r) {
        if (*(L + i) >= *(L + j)) {
            queue_enqueue(Sorted, L + j);
            i++;
        }
        else {
            queue_enqueue(Sorted, L + i);
            j++;
        }
    }
}

template<typename T>
void Merge_sort(int* L, int p, int r) {
    int q = 0;
    if (p < r) {
        q = (p + r) / 2;
        Merge_sort<T>(L, p, q);
        Merge_sort<T>(L, q + 1, r);
        Merge<T>(L, p, q, r);
    }
}



int main() {
    int n = 5;
    int l_max = 0;
    size_t elem_size_ = sizeof(size_t);
    size_t capacity_ = 10;
    Queue<size_t>* q = queue_init<size_t>(capacity_);
    for (int i=0; i < n; i++) {
        size_t p(rand());
        
        if (p % 2 == 0) { queue_enqueue(q, &p); }
        else { queue_dequeue(q, &p); }
        if (queue_length(q) > l_max) { l_max = queue_length(q); }
    }
    std::cout << l_max << "     "<<*( (size_t*)(q->data)) << "\n";
    return l_max;
}