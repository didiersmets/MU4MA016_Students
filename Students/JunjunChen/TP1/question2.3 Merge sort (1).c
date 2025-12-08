#include <stdio.h>
#include <stdlib.h>

// question 2.3 Merge sort
void merge(int *T, int p, int q, int r) {
    int n1 = q - p + 1;           // left
    int n2 = r - q;               // right

    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++)
        L[i] = T[p + i];
    for (int j = 0; j < n2; j++)
        R[j] = T[q + 1 + j];

    int i = 0, j = 0, k = p;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            T[k++] = L[i++];
        } else {
            T[k++] = R[j++];
        }
    }

    while (i < n1)
        T[k++] = L[i++];
    while (j < n2)
        T[k++] = R[j++];

    free(L);
    free(R);
}

void merge_sort(int *T, int p, int r) {
    if (p < r) {
        int q = (p + r) / 2;      // ⌊(p+r)/2⌋
        merge_sort(T, p, q);
        merge_sort(T, q + 1, r);
        merge(T, p, q, r);
    }
}

// for test
int main() {
    int arr[] = {11, 54, 23, 6, 7, 89, 4, 2, 8, 45};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("原数组: ");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");

    merge_sort(arr, 0, n - 1);

    printf("排序后: ");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");

    return 0;
}
