#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include <time.h> 

//THIS FOLLOWING CODE IS TAKEN FROM LECTURE NOTES
void merge(const float *A, int sA, const float *B, int sB, float *C){//ATTENTION: Here it is assumed that A and B are already in increasing order
    int idxA = 0;
    int idxB = 0;
    for (int idxC = 0; idxC < sA + sB; idxC++) {
        /* if A has not been emptied yet and either B was emptied or
        * the tracked element in A is smaller than the one in B,
        * we pick from A */
        if ((idxA < sA) && ((idxB == sB)|| A[idxA] <= B[idxB])){
            C[idxC] = A[idxA++];
            }
        /* otherwise we necessarily pick from B */
        else{
            C[idxC] = B[idxB++];
            }
        }
    }

void merge_sort(float* T, int lengthT, int n){// here int n is the length of the last little array that will be merg sorted
 /*   
    printf("[");
    for (int i=0; i<lengthT; i++){
        printf(" %f ",T[i]);
    }
    printf("]\n");
 */
   
    //check if you have reached the smallest size
    if (lengthT<2){return;}

    int mid = lengthT/2; //we want integer division
    float* A=malloc(mid*sizeof(float));

    int mid_to_end=lengthT-mid;
    float* B=malloc(mid_to_end*sizeof(float));

    for (int j=0;j<mid; j++){
        A[j]=T[j];
    }

    for (int k=mid;k<lengthT;k++){
        B[k-mid]=T[k];
    }
/*
    printf("PRINTING B:");
    printf("%d", mid_to_end);
    for (int i=0; i<mid_to_end; i++){
        printf(" %f ",B[i]);
    }
    printf("\n");


    memcpy(A, T, sizeof(float)*mid);
    memcpy(A, T+mid_to_end*sizeof(float), sizeof(float)*mid_to_end);
*/
    
    merge_sort(A,mid, n);
    merge_sort(B,mid_to_end ,n);
    merge(A, mid, B, mid_to_end, T);

    free(A);
    free(B);
}

int main(int argc, char** argv){ //arguments needed are  1.) length of the list and 2.) what the smallest list should be that is then sorted.
    int tini=atoi(argv[2]);
    int lengthT=atoi(argv[1]);
    srand(time(NULL));

    float* T=malloc(sizeof(float)*lengthT);
    for (int i=0; i<lengthT; i++){
        T[i]=rand() % 50 ;
    }
    printf("[");
    for (int i=0; i<lengthT; i++){
        printf(" %f ",T[i]);
    }
    printf("]\n");

    merge_sort(T,lengthT, tini);

    printf("[");
    for (int i=0; i<lengthT; i++){
        printf(" %f ", T[i]);
    }
    printf("]\n");

    free(T);
    return 0;
}