#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    int *L = (int*)malloc(n1 * sizeof(int));
    int *R = (int*)malloc(n2 * sizeof(int));
    for (i = 0; i < n1; i++) L[i] = arr[l + i];
    for (j = 0; j < n2; j++) R[j] = arr[m + 1 + j];
    i = 0; j = 0; k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
    free(L);
    free(R);
}


void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}


int main() {
    srand(time(NULL));
    int sizes[] = {10, 20, 50, 100, 200, 500, 1000};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);
    FILE *dataFile = fopen("merge_times.dat", "w");
    if (dataFile == NULL) { fprintf(stderr, "Error: Could not open file for writing.\n"); return 1; }
    for (int i = 0; i < num_sizes; i++) {
        int N = sizes[i];
        int* arr = (int*)malloc(N * sizeof(int));
        if (arr == NULL) { fprintf(stderr, "Memory allocation failed.\n"); return 1; }
        for (int j = 0; j < N; j++) { arr[j] = rand(); }
        clock_t start = clock();
        mergeSort(arr, 0, N - 1);
        clock_t end = clock();
        double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
        printf("N = %d, Time = %f seconds\n", N, time_spent);
        fprintf(dataFile, "%d %f\n", N, time_spent);
        free(arr);
    }
    fclose(dataFile);
    FILE *gnuplotScript = fopen("plot_script_merge.gp", "w");
    if (gnuplotScript == NULL) { fprintf(stderr, "Error: Could not create gnuplot script.\n"); return 1; }
    fprintf(gnuplotScript, "set terminal pngcairo size 800,600\nset output 'merge_sort_performance.png'\n");
    fprintf(gnuplotScript, "set title 'Merge Sort Performance'\nset xlabel 'Number of elements (N)'\nset ylabel 'Execution time (seconds)'\n");
    fprintf(gnuplotScript, "set logscale xy\nset grid\nplot 'merge_times.dat' with linespoints title 'Merge Sort'\n");
    fclose(gnuplotScript);
    printf("Generating plot 'merge_sort_performance.png'...\n");
    system("gnuplot plot_script_merge.gp");
    return 0;
}
