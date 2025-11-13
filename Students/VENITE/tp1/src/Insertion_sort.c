#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void insertionSort(int arr[], int n) {
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}


int main() {
    srand(time(NULL));
    int sizes[] = {10, 20, 50, 100, 200, 500, 1000};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);
    FILE *dataFile = fopen("insertion_times.dat", "w");
    if (dataFile == NULL) { fprintf(stderr, "Error: Could not open file for writing.\n"); return 1; }
    for (int i = 0; i < num_sizes; i++) {
        int N = sizes[i];
        int* arr = (int*)malloc(N * sizeof(int));
        if (arr == NULL) { fprintf(stderr, "Memory allocation failed.\n"); return 1; }
        for (int j = 0; j < N; j++) { arr[j] = rand(); }
        clock_t start = clock();
        insertionSort(arr, N);
        clock_t end = clock();
        double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
        printf("N = %d, Time = %f seconds\n", N, time_spent);
        fprintf(dataFile, "%d %f\n", N, time_spent);
        free(arr);
    }
    fclose(dataFile);
    FILE *gnuplotScript = fopen("plot_script_insertion.gp", "w");
    if (gnuplotScript == NULL) { fprintf(stderr, "Error: Could not create gnuplot script.\n"); return 1; }
    fprintf(gnuplotScript, "set terminal pngcairo size 800,600\nset output 'insertion_sort_performance.png'\n");
    fprintf(gnuplotScript, "set title 'Insertion Sort Performance'\nset xlabel 'Number of elements (N)'\nset ylabel 'Execution time (seconds)'\n");
    fprintf(gnuplotScript, "set logscale xy\nset grid\nplot 'insertion_times.dat' with linespoints title 'Insertion Sort'\n");
    fclose(gnuplotScript);
    printf("Generating plot 'insertion_sort_performance.png'...\n");
    system("gnuplot plot_script_insertion.gp");
    return 0;
}
