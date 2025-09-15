#include <stdio.h>

int main(int argc, char* argv[]){

    int n = *argv[1] - 48;
    printf("n : %d", n);

    for(int i = 0; i < n; i++){
        for(int j = 0; j <= i; j++){

            if((j == 0) || (i == j)) {
                printf("1 ");
            }else{
                printf( " ");
            }
        }
        printf("\n");
    }
    return 0;
}