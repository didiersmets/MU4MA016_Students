#include <stdio.h>

void bubble_sort(int *T, int n) {
    for (int i = 0; i < n - 1; i++) {
        int swapped = 0; // petite optimisation : si aucun swap, on peut arrêter
        for (int j = 0; j < n - 1 - i; j++) {
            if (T[j] > T[j + 1]) {
                int tmp = T[j];
                T[j] = T[j + 1];
                T[j + 1] = tmp;
                swapped = 1;
            }
        }
        if (!swapped) break;
    }
}
