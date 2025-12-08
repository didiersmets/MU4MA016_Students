#include <assert.h>
#include <stdio.h>
#include <stdlib.h>


// question 3 Loops and formatted output (2)
int main(int argc, char* argv[]) {
    int n;

    if (argc == 2) {
        n = atoi(argv[1]);
    } else {
        printf("Usage: %s n\n", argv[0]);
        printf("No argument given. Please enter n: ");
        if (scanf_s("%d", &n) != 1) {
            printf("Invalid input. \n");
            return 1;
        }
    }
    if (n <= 0) {
        printf("n must be positive. \n");
        return 1;
    }

    long long *prev = (long long *)calloc(n + 1, sizeof(long long));
    long long *curr = (long long *)calloc(n + 1, sizeof(long long));
    if (!prev || !curr) {
        printf("Memory allocation failed. \n");
        free(prev);
        free(curr);
        return 1;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            if (j == 0 || j ==1) {
                curr[j] = 1;
            } else {
                curr[j] = prev[j - 1] + prev[j];
            }
            printf("lld ", curr[j]);
        }
        printf("\n");

        long long *tmp = prev;
        prev = curr;
        curr = tmp;

        for (int j = 0; j <= i; j++) {
            curr[j] = 0;
        }
    }
    free(prev);
    free(curr);
    return 0;
}
