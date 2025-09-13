#include <stdio.h>
#include <stdlib.h>

int printArray(int* array, int count) {
    for (int i =0; i < count; i++) {
        printf("%i ", array[i]);
    }
    printf("\n");
}

int main(int argc, char* args[]) {
    if (argc != 2) {
        printf("Expected 1 argument (n)");
        return 1;
    }
    int n = atoi(args[1]);

    int* A = malloc(n * sizeof(int));

    for(int i=0; i < n; i++) {
        A[0] = 1;
        A[i] = 1;
        for(int j=i-1; j > 0; j--) {
            A[j] += A[j-1];
        }
        printArray(A, i + 1);
    }

    free(A);

    return 0;
}