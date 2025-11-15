
#include <stdio.h>

// ---- merge sort: hjälpfunktion som slår ihop två sorterade halvor ----
// Slår ihop arr[left..mid] och arr[mid+1..right] in-place med temporära VLA-buffertar.
void sub_merge(int *arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int L[n1], R[n2];           // VLA: kräver C99
    for (int i = 0; i < n1; ++i) L[i] = arr[left + i];
    for (int j = 0; j < n2; ++j) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else              arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

// Rekursiv del av merge sort
static void merge_sort_rec(int *arr, int left, int right) {
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    merge_sort_rec(arr, left, mid);
    merge_sort_rec(arr, mid + 1, right);
    // Slå bara ihop om det behövs
    if (arr[mid] > arr[mid + 1]) sub_merge(arr, left, mid, right);
}

// Publik merge_sort
void merge_sort(int *arr, int n) {
    if (n > 1) merge_sort_rec(arr, 0, n - 1);
}

// ---- main ----
int main(void) {
    // 1. Skapa en array med några heltal
    int arr[] = {11, 54, 23, 6, 7, 89, 4, 2, 8, 45};
    int n = sizeof(arr) / sizeof(arr[0]); // beräknar antal element

    // 2. Skriv ut arrayen före sortering
    printf("Före sortering:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // 3. Anropa merge_sort (byt till bubble_sort(arr, n); om du vill ha exakt som tidigare)
    merge_sort(arr, n);

    // 4. Skriv ut arrayen efter sortering
    printf("Efter sortering:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0; // talar om att programmet slutade utan fel
}
