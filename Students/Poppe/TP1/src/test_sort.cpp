// g++ src/test_sort.cpp src/bubble_sort.cpp src/insertion_sort.cpp -I include -o test_queue -std=c++17

#include <utility>
#include <string>
#include <functional>
#include <chrono>
#include <iostream>

#include "bubble_sort.hpp"
#include "insertion_sort.hpp"

std::pair<std::function<void (int*, size_t)>, std::string> algorithms[] = {
    std::make_pair(bubble_sort, "Bubble sort"), 
    std::make_pair(insertion_sort, "Insertion sort")
};

int* init_array(size_t n) {
    int* array = new int[n];
    for (size_t i=0;i<n;i++) {
        array[i] = rand() % 1000;
    }
    return array;
}

std::chrono::duration<double> time_size(std::function<void (int*, size_t)> algorithm, size_t n) {
    int* array = init_array(n);
    auto start = std::chrono::high_resolution_clock::now();
    algorithm(array, n);
    auto end = std::chrono::high_resolution_clock::now();
    delete[] array;
    return end - start;
}

constexpr int sizes[] = {10, 20, 50, 100, 200, 500, 1000};

void time_algorithm(std::function<void (int*, size_t)> algorithm, const std::string& name) {
    for (size_t n : sizes) {
        auto duration = time_size(algorithm, n);
        std::cout << name << " with size " << n << " took " << duration.count() << " seconds." << std::endl;
    }
}


int main() {
    for (const auto& [algorithm, name] : algorithms) {
        time_algorithm(algorithm, name);
    }
    return 0;
}