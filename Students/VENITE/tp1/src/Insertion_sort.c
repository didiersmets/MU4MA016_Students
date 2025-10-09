#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Insertion sort
void insertion_sort(int *arr, int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

int main() {
    int N = 10;
    int arr[N];

    // remplir le tableau avec des nombres aléatoires
    srand((unsigned int)time(NULL));
    for (int i = 0; i < N; i++)
        arr[i] = rand() % 100;

    printf("Avant tri : ");
    for (int i = 0; i < N; i++)
        printf("%d ", arr[i]);
    printf("\n");

    insertion_sort(arr, N);

    printf("Après tri : ");
    for (int i = 0; i < N; i++)
        printf("%d ", arr[i]);
    printf("\n");

    return 0;
}
