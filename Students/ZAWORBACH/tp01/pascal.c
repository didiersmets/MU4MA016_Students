#include <stdio.h>
#include <stdlib.h>

int pascal_num (int i, int j)
{
    if (0<j && j<i){
        return pascal_num(i-1,j-1) + pascal_num(i-1,j);
    }
    return 1;
}

int pascal_triange(int n){
    for (int i=0;i<n;i++){
        printf("\n");
        for(int j=0;j<i;j++){
            printf("%d\t", pascal_num(i,j));
        }
    }

    return 0;
}

int main (int argc, char **argv){
    if (argc != 2){
        fprintf(stderr, "Usage: %s <num_rows>\n", argv[0]);
        return 1;
    }
    int n = atoi(argv[1]);
    pascal_triange(n);
    return 0;

}