#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Bubble Sort -----------------------------------------------------------------------
void bubble_sort(int* seq, int length){

    if(length == 1){
        return;
    }

    for(int i = 0; i < length - 1; i++) {
        int current = seq[i];
        int next = seq[i + 1];

        if(current > next){
            seq[i] = next;
            seq[i + 1] = current;
        }
    }

    bubble_sort(seq, length-1);
}

//Insertion Sort ---------------------------------------------------------------------
void insertion_sort(int* seq, int length){

    for(int i = 1; i < length; i++){
        int current = seq[i];
        int j = i - 1;

        while ((current < seq[j]) && (j >= 0)){
            seq[j + 1] = seq[j];
            seq[j] = current;
            j--;
        }
    }
}

//Merge Sort -------------------------------------------------------------------------
void merge(int *from, int *to, int p, int q, int r){

    int i = 0;
    int j = 1;

    for(int k = p; k <= r; k++){

        if((p + i <= q) && ((q + j > r) || (from[p + i] <= from[q + j]))){

            to[k] = from[p + i];
            i++;

        }else if ((q + j <= r) && ((p + i > q ) || (from[p + i] > from[q + j])))
        {
            to[k] = from[q + j];
            j++;
        }
    }
}

void merge_sort_rec(int *from, int *to, size_t begin, size_t end){
    if(begin < end){
        int q = (begin + end)/2;

        merge_sort_rec(to, from, begin, q);
        merge_sort_rec(to, from, q + 1, end);
        merge(from, to, begin, q, end);
    }
}

void merge_sort(int* seq, int length){
    size_t size = length * sizeof(int);     //size in memory of our sequence
    int *B = (int *) malloc(size);
    memcpy(B, seq, size);                   //Copy of the sequence into B

    merge_sort_rec(B, seq, 0, length - 1);  //Sort B into seq
    free(B);
}

int main(int argc, char **argv){

    int A[] = {11,54,23,6,7,89,4,2,8,45};
    int lenA = sizeof(A)/sizeof(int);

    bubble_sort(A, lenA);
    printf("Bubble sort : ");
    for(int i = 0; i < lenA; i++){
        printf("%d ", A[i]);
    }

    int B[] = {11,54,23,6,7,89,4,2,8,45};
    int lenB = sizeof(B)/sizeof(int);

    insertion_sort(B, lenB);
    printf("\nInsertion sort : ");
        for(int i = 0; i < lenB; i++){
        printf("%d ", B[i]);
    }

    int C[] = {11,54,23,6,7,89,4,2,8,45};
    int lenC = sizeof(C)/sizeof(int);

    merge_sort(C, lenC);
    printf("\nMerge sort : ");
        for(int i = 0; i < lenC; i++){
        printf("%d ", C[i]);
    }

    printf("\n");

    return 0;
}