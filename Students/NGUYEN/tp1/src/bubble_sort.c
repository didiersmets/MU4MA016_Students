#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stddef.h>
#include <stdbool.h>
#include <assert.h>

void bubble_sort(int *t, int l){ //t = address and l = number of elements
    
    for (int i = 0; i < l-1; i++){
        for (int j = 0; j < l-1; j++){
            if (t[j] > t[j+1]){
                int temp = t[j];
                t[j] = t[j+1];
                t[j+1] = temp;
            }
        }
    }
    return;
}

int main(){
    int array_N[7] = {10, 20, 50, 100, 200, 1000, 50000};
    FILE *bubble = fopen("../bubble_sort.dat", "w");

    for (int i = 0; i < 7; i++){
        int N = array_N[i];
        int *T = malloc(N*sizeof(int));

        for (int j = 0; j < N; j++){
            int r = rand();
            T[j] = r; 
        }

        int *tab_bubble = malloc(N*sizeof(int));
        for (int k = 0; k < N; k++){
            tab_bubble[k] = T[k];
        }
        clock_t time = clock();
        bubble_sort(tab_bubble, N);
        time = clock() - time;
        double time_in_sec = ((double)time)/ CLOCKS_PER_SEC;
        fprintf(bubble, "%d\t%f\n", N, time_in_sec);
        free(tab_bubble);
        free(T);
    }
    fclose(bubble);
    return 0;
}