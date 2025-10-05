#include <stdio.h>
#include <stdlib.h>

static void merge(int *T, int p, int q, int r) {
    int n = r - p + 1;
    int *tmp = (int*)malloc(n * sizeof(int));
    if (!tmp) { printf("malloc a echoue dans merge\n"); exit(1); }

    int i = p;       // pointeur sous-tableau gauche
    int j = q + 1;   // pointeur sous-tableau droit
    int k = 0;       // pointeur tmp

    while (i <= q && j <= r) {
        if (T[i] <= T[j]) tmp[k++] = T[i++];
        else              tmp[k++] = T[j++];
    }
    while (i <= q) tmp[k++] = T[i++];
    while (j <= r) tmp[k++] = T[j++];

    // recopie dans T
    for (k = 0; k < n; ++k) T[p + k] = tmp[k];

    free(tmp);
}

static void merge_sort_rec(int *T, int p, int r) {
    if (p < r) {
        int q = (p + r) / 2;
        merge_sort_rec(T, p, q);
        merge_sort_rec(T, q + 1, r);
        merge(T, p, q, r);
    }
}

void merge_sort_array(int *T, int n) {
    if (n > 0) merge_sort_rec(T, 0, n - 1);
}
