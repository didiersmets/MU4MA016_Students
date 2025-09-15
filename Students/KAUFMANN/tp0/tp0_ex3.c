#include <stdio.h>

int pascal(int N) {
    int A[N][N]; 
    A[0][0] = 1;
    for (int i = 1; i < N; i++) {
        A[i][0] = 1;
        printf("%d ", A[i][0]);
        for (int j = 1; j < i; j++) {
            A[i][j] = A[i-1][j-1] + A[i-1][j];
            printf("%d", A[i][j]);
        }
        A[i][i] = 1;
        printf("%d\n", A[i][i]);
    }
    return 0;
}

int main() {
    int n;
    printf("N = ");
    scanf("%d", &n);
    pascal(n);
    return 0;
}
