
#include <stdio.h>

void insertion_sort(int *arr, int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        // Flytta större element ett steg uppåt
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

int main(void) {
    int arr[] = {8, 3, 1, 7, 0, 10, 2};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Före insertion_sort:\n");
    for (int i = 0; i < n; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    insertion_sort(arr, n);

    printf("Efter insertion_sort:\n");
    for (int i = 0; i < n; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
