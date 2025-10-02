#include <stdio.h>

int main() {
    printf("Entrer le nombre de lignes du triangle de Pascal : ");
    int n;
    scanf("%d", &n);

    if (n<=0) {
        printf("Erreur : le nombre de lignes doit être un entier positif.\n");
        return 1;
    }

    // tableau 2D pour stocker les coeff
    int pascal[20][20];

    // construction du triangle de Pascal
    for (int i=0; i<n; i++) {
        for (int j=0; j<=i; j++) {
            if (j==0 || j==i) {
                pascal[i][j] = 1; // bords du triangle=1
            }
            else {
                pascal[i][j] = pascal[i-1][j-1] + pascal[i-1][j]; // coeff interieurs
            } 
        }
    }

    // Affichage du triangle de Pascal
    for (int i=0; i<n; i++) {
        for(int j=0; j<=i; j++) {
            printf("%d", pascal[i][j]);
        }
        printf("\n");
    }
    return 0;
}