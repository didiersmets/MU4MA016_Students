#include <stdio.h>

// tri par insertion
void insertion_sort(int *T, int n) {
    for (int i = 1; i < n; i++) {
        int key = T[i];
        int j = i - 1;

        // décaler tous les éléments > key
        while (j >= 0 && T[j] > key) {
            T[j + 1] = T[j];
            j--;
        }
        T[j + 1] = key;
    }
}
