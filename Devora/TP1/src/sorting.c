#include "sorting.h"
#include <stdio.h>

void bubble_sort(int * array, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (array[j] > array[j + 1]) {
                int tmp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = tmp;
            }
        }
    }
}

void insertion_sort(int * array, int n) {
    for (int i = 1; i < n; i++) {
        int key = array[i];
        int j = i - 1;
        while (j >= 0 && array[j] > key) {
            array[j + 1] = array[j];
            j--;
        }
        array[j + 1] = key;
    }
}

void merge(int *T, int p, int q, int r) {
    int n1 = q - p + 1;
    int n2 = r - q;
    int L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = T[p + i];
    for (int j = 0; j < n2; j++)
        R[j] = T[q + 1 + j];

    int i = 0, j = 0, k = p;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            T[k] = L[i];
            i++;
        } else {
            T[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        T[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        T[k] = R[j];
        j++;
        k++;
    }
}

void merge_sort(int *T, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        merge_sort(T, left, mid);
        merge_sort(T, mid + 1, right);
        merge(T, left, mid, right);
    }
}
