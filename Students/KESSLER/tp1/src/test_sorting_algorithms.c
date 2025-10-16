#include "bubblesort.h"
#include "insertionsort.h"
#include "mergesort.h"
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

// Function to create a copy of the array for each sorting algorithm
int* copy_array(const int* source, size_t length) {
    int* copy = malloc(length * sizeof(int));
    memcpy(copy, source, length * sizeof(int));
    return copy;
}

// Function to measure execution time of a sorting algorithm
double measure_sort_time(void (*sort_func)(int*, size_t), int* array, size_t length) {
    clock_t start = clock();
    sort_func(array, length);
    clock_t end = clock();
    return ((double)(end - start)) / CLOCKS_PER_SEC;
}

int main() {
    srand(time(NULL));
    
    // Array of N values to test
    size_t N_values[] = {10, 20, 50, 100, 200, 500, 1000};
    size_t num_tests = sizeof(N_values) / sizeof(N_values[0]);
    
    // Open file for writing results
    FILE* data_file = fopen("sorting_times.dat", "w");
    fprintf(data_file, "# N\tBubbleSort\tInsertionSort\tMergeSort\n");
    
    for (size_t i = 0; i < num_tests; i++) {
        size_t N = N_values[i];
        
        // Generate random array
        int* original = malloc(N * sizeof(int));
        for (size_t j = 0; j < N; j++) {
            original[j] = rand() % 10000;
        }
        
        // Create copies for each sorting algorithm
        int* bubble_arr = copy_array(original, N);
        int* insertion_arr = copy_array(original, N);
        int* merge_arr = copy_array(original, N);
        
        // Measure sorting times
        double bubble_time = measure_sort_time(bubblesort, bubble_arr, N);
        double insertion_time = measure_sort_time(insertionsort, insertion_arr, N);
        double merge_time = measure_sort_time(merge_sort, merge_arr, N);
        
        fprintf(data_file, "%zu\t%f\t%f\t%f\n", N, bubble_time, insertion_time, merge_time);
        
        free(original);
        free(bubble_arr);
        free(insertion_arr);
        free(merge_arr);
    }
    
    fclose(data_file);
    
    // gnuplot
    FILE* gnuplot_script = fopen("plot_script.gnu", "w");
    fprintf(gnuplot_script, 
        "set terminal png\n"
        "set output 'sorting_comparison.png'\n"
        "set title 'Sorting Algorithm Performance Comparison'\n"
        "set xlabel 'Array Size (N)'\n"
        "set ylabel 'Time (seconds)'\n"
        "set logscale xy\n"
        "set grid\n"
        "plot 'sorting_times.dat' using 1:2 title 'Bubble Sort' with linespoints,\\\n"
        "     'sorting_times.dat' using 1:3 title 'Insertion Sort' with linespoints,\\\n"
        "     'sorting_times.dat' using 1:4 title 'Merge Sort' with linespoints\n"
    );
    fclose(gnuplot_script);
    
    system("gnuplot plot_script.gnu");
    
    return 0;
}