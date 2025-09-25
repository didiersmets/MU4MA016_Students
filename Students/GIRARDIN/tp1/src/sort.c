#include <stdio.h>
#include <stdlib.h>

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
void merge_sort(int* seq, int length){

}