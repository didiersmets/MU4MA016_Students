#include <stdio.h>
#include <stdlib.h>

int calculate_recursive_pascal(int i, int j){
    int a;
            if (j == 0 || j == i) {
                a = 1;
            }
            else {
                a = calculate_recursive_pascal(i-1,j-1)+ calculate_recursive_pascal(i-1,j);
            }    
    return a;
}
int recursive_pascal(int n){
    for (int i = 0; i <n; i++){
        for (int j = 0; j <= i; j++){
            int a = calculate_recursive_pascal(i,j);
            printf("%d ",a);
        }
        printf("\n");
    }
    return 0;
}

int main() {
    printf("Enter number pls \n");
    int n;
    scanf("%d", &n);

    int **A = malloc(n * sizeof(int *)); //pointer to pointer to int(array)
    for (int i = 0; i < n; i++) {
        A[i] = malloc(n * sizeof(int)); //by accessing A[i], i get the pointer to the row. by ysing malloc I get actually good memeory address
    }

    for (int i = 0; i < n; i++) {
        // Print leading spaces for pyramid shape
        for (int s = 0; s < n - i - 1; s++) {
            printf("  ");
        }

        for (int j = 0; j <= i; j++) {
            if (j == 0 || j == i) {
                A[i][j] = 1;
            } else {
                A[i][j] = A[i - 1][j - 1] + A[i - 1][j];
            }
            printf("%d   ", A[i][j]); // extra spaces for alignment
        }
        printf("\n");
    }

    // Free memory
    for (int i = 0; i < n; i++) {
        free(A[i]);
    }
    free(A);


    printf("\n\n");
    recursive_pascal(n);
    return 0;
}