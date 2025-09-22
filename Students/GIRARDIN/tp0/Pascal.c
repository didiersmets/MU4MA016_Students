#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){

    int n = atoi(argv[1]);
    printf("### n : %d \n", n);

    int pasc[n+1][n+1];

    for(int i = 0; i <= n; i++){
        for(int j = 0; j <= i; j++){

            if((j == 0) || (i == j)) {
                pasc[i][j] = 1;
            }else{
                pasc[i][j] = pasc[i-1][j-1] + pasc[i-1][j];
            }
            printf("%d ", pasc[i][j]);
        }
        printf("\n");
    }
    return 0;
}