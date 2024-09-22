#include <stdio.h>

long long factorial(int num) {
    long long fact = 1;
    for (int i = 1; i <= num; i++) {
        fact *= i;
    }
    return fact;
}

long long binomialCoefficient(int n, int k) {
    return factorial(n) / (factorial(k) * factorial(n - k));
}

void printPascalsTriangle(int n) {
    for (int i = 0; i < n; i++) {
        // Print leading spaces for proper formatting
        for (int j = 0; j < n - i - 1; j++) {
            printf("  ");
        }
        
        // Print each value in the ith row
        for (int k = 0; k <= i; k++) {
            printf("%4lld ", binomialCoefficient(i, k));
        }
        printf("\n");
    }
}

int main() {
    int n;

    // Prompt user to enter number of lines
    printf("Enter the number of lines for Pascal's triangle: ");
    scanf("%d", &n);

    // Print Pascal's triangle
    printPascalsTriangle(n);

    return 0;
}
