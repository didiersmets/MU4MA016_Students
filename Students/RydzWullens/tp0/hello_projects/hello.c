#include <stdio.h>

int main() {

    int n;

    printf("enter number of row of pascals traingle: ");
    scanf("%d", &n);
    
    int traingle[n*(n+1)/2];
    traingle[0] = 1;

    for (int i = 0; i < n; i++) {

        printf("\n");

        for (int j = 0; j <= i; j++){

            int new;

            if (j > 0 && j < i) {

                new = traingle[i*(i-1)/2+j-1] + traingle[i*(i-1)/2+j];
                traingle[i*(i+1)/2+j] = new;

            }

            else {

                new = 1;
                traingle[i*(i+1)/2+j] = 1;
            }

            printf("%d ", new);

        }

    }
}
