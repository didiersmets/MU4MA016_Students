#include "sorting.h"
#include <stdlib.h>

void merge(int* T, int p, int q, int r){
    int i = p+0;
    int j = q+1;
    int n = 0;
    int N = r-p+1;   
    int *B = (int*)malloc((r - p + 1) * sizeof(int)); //temporary array for sorting
    while(n < N){
        if(i<=q && j<=r){
            if(T[i]>T[j]){
                B[n]=T[j];
                j+=1;
            }else{
                B[n]=T[i];
                i+=1;
            }
            n+=1;
        }else if(i>q /*&& j<=r*/){
            B[n]=T[j];
            n+=1;
            j+=1;
        }else if(j>r /*&& i<=q*/){
            B[n]=T[i];
            n+=1;
            i+=1;
        }
    }
    //copy back to T
    for (int i = 0; i <= (r - p); i++) {
    T[p + i] = B[i]; 
    }
    free(B);
}

void merge_sort(int *T, int p, int r){
    int q;
    if(p<r){
        q = (p+r)/2;
        merge_sort(T, p, q);
        merge_sort(T, q+1, r);
        merge(T, p, q, r);
    }
}

