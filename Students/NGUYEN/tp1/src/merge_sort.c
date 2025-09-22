#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stddef.h>
#include <stdbool.h>
#include <assert.h>

void merge_sort(int *t, int l){ // t = address of the array and l = number of elements

    /*
    for (int i = 1; i < l-1; i++){
        for (int j = i; j > 0; j--){ // decreasing from i (the current sequence)
            if (t[j] > t[j+1]){
                int temp = t[j];
                t[j] = t[j+1];
                t[j+1] = temp;
            } else {
                break; // if we don't need to swap we break the loop to go to the next sequence
            }
        }
    }
    */
    return;
}

int main(){
    int array_N[7] = {10, 20, 50, 100, 200, 500, 1000};
    FILE *merge = fopen("../merge_sort.dat", "w");

    for (int i = 0; i < 7; i++){
        int N = array_N[i];
        int *T = malloc(N*sizeof(int));

        for (int j = 0; j < N; j++){
            int r = rand();
            T[j] = r; 
        }

        int *tab_merge = malloc(N*sizeof(int));
        for (int k = 0; k < N; k++){
            tab_merge[k] = T[k];
        }
        clock_t time = clock();
        merge_sort(tab_merge, N);
        time = clock() - time;
        double time_in_sec = ((double)time)/ CLOCKS_PER_SEC;
        fprintf(merge, "%d\t%f\n", N, time_in_sec);
        free(tab_merge);
        free(T);
    }
    fclose(merge);
    return 0;
}