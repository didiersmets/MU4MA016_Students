#include <stdio.h>
#include <stdlib.h>
#include <time.h>


static void merge(int *arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int *L = malloc(n1 * sizeof(int));
    int *R = malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    free(L);
    free(R);
}

static void merge_sort_rec(int *arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        merge_sort_rec(arr, left, mid);
        merge_sort_rec(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

void merge_sort(int *arr, int n) {
    merge_sort_rec(arr, 0, n - 1);
}

int main() {
    int N = 10;
    int arr[N];

    srand((unsigned int)time(NULL));
    for (int i = 0; i < N; i++)
        arr[i] = rand() % 100;

    printf("Avant tri : ");
    for (int i = 0; i < N; i++)
        printf("%d ", arr[i]);
    printf("\n");

    merge_sort(arr, N);

    printf("Après tri : ");
    for (int i = 0; i < N; i++)
        printf("%d ", arr[i]);
    printf("\n");

    return 0;
}
