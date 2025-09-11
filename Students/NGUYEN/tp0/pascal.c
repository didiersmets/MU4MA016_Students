#include <stdio.h>

void print_pascal(int n) {
    //int pascal[n][n] = {0}; // maybe malloc and free after ?
    
    int pascal[1000][1000] = {0}; // n cant be >1000

    for (int i = 0; i < n; i++){
        for (int j = 0; j <= i; j++){
            if (j == 0 || j == i) {
                pascal[i][j] = 1;
            } else {
                pascal[i][j] = pascal[i-1][j-1] + pascal[i-1][j];
            }
            printf("%d", pascal[i][j]);
        }
        printf("\n");
    }
}



int main() {
    int n; 
    printf("n = ??? (not greater than 1000 please)\n");
    scanf("%d", &n);

    if (n <= 0 || n > 1000) {
        printf("not a positive integer or too big\n");
        return 1;
    }
    print_pascal(n);
    return 0;
}