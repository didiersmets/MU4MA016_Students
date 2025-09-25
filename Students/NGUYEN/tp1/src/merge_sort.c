#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stddef.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>

void merge_subroutine(int *T, int p, int q, int r){
    assert((p <= q) && (q < r));
    // T[p], T[p + 1]...T[q] and T[q +1], T[q + 2]...T[r] are already sorted

    /*First, we compare T[p] et T[q+1]. We retain the smallest of the two,
and we save it. Let’s say it was T[p] here, we then compare T[p+1] et T[q+1], retain the smallest
of the two, and save it for positioning in second place in the final sequence. Et caetera.
*/
    
    int small1 = p; // first int of the first subsequence
    int small2 = q+1; // first int of the second subsequence
    int *T_temp = malloc((r-p+1) * sizeof(int)); // to save the smallest at each iteration

    for (int i = 0; i < r-p+1; i++){
        if ((small1 <= q)&&((T[small1] <= T[small2])||(small2 > r))){ // order in the && is very important (we have to check if small1 is inbounds first)
            T_temp[i] = small1;
            small1++; // we increment only small1
        } else {
            T_temp[i] = small2;
            small2++; // we increment only small2 
        }
    }

    for (int j = 0; j < r-p+1; j++){ // a memcpy may be better
        T[j+p] = T_temp[j];
    }
    free(T_temp);
    return;
}

void merge_sort(int *T_temp, int p, int r){ 

    /* in pseudo code : 

    MergeSort(T, p, r)
    if (p<r) {
        q = integer_part((p+r)/2)
        MergeSort(T, p, q)
        MergeSort(T, q + 1, r)
        Merge(T, p, q, r)
    }
    To sort the whole array, it suffices to call MergeSort with p = 0 and r = length(T) - 1.
    */

    /*
    //if we want to try the ping-pong version
    int *T_temp = malloc((r-p+1) * sizeof(int));
    memcpy(T_temp, T, (r-p+1) * sizeof(int)); // to not lose the original array during the sorting
    */

    if (p<r){
        int q = (int)((p+r)/2); // we use a cast but we could use math.floor or math.trunc
        merge_sort(T_temp, p, q);
        merge_sort(T_temp, q+1, r);
        merge_subroutine(T_temp, p, q, r);
    }
    
    return;
}

int main(){
    int array_N[7] = {10, 20, 50, 100, 200, 1000, 50000};
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
        merge_sort(tab_merge, 0, N-1);
        time = clock() - time;
        double time_in_sec = ((double)time)/ CLOCKS_PER_SEC;
        fprintf(merge, "%d\t%f\n", N, time_in_sec);
        free(tab_merge);
        free(T);
    }
    fclose(merge);
    return 0;
}