#include <stddef.h> // for size_t
#include <sorting_algorithms.hpp>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

void swap(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void bubble_sort(int* array, int length){
    for (int i = 0; i < length-1; i++){
        for (int j = 0; j < length-i-1; j++){
            if (array[j] > array[j+1]){
                swap(&array[j], &array[j+1]);
            }
        }
    }
}


void insertion_sort(int* array, int length){
    for(int i = 1; i < length; i++){
        int j = i;
        while(array[j] < array[j-1] && j > 0){
            swap(&array[j], &array[j-1]);
            j = j - 1;
        }
    }
}


void merge(int* from, int* to, size_t begin, size_t middle, size_t end){
    int i=0;
    int j=0;
    for(int n = begin; n <= end; n++){
        if(begin+i <= middle && middle+1+j <= end){
            if(from[begin+i] <= from[middle+1+j]){
                to[n] = from[begin+i];
                i++;
            }
            else {
                to[n] = from[middle+1+j];
                j++;
            }
        }
        else if(begin+i > middle){
            to[n] = from[middle+1+j];
                j++;
        }
        else if(middle+1+j > end){
            to[n] = from[begin+i];
                i++;
        }
    }
}


void merge_sort_recursive(int* from, int* to, size_t begin, size_t end){
    if(end != begin){
        int middle = floor((begin+end)/2);
        merge_sort_recursive(to,from,begin,middle);
        merge_sort_recursive(to,from,middle+1,end);
        merge(from,to,begin,middle,end);
    }
}

void merge_sort(int* B, size_t length){
    int *A = (int*)malloc(length*sizeof(int));
    memcpy(A,B,length*sizeof(int));
    int begin = 0;
    int end = length - 1;
    int middle = floor((begin+end)/2);
    merge_sort_recursive(B,A,begin,middle);
    merge_sort_recursive(B,A,middle+1,end);
    merge(A,B,begin,middle,end);
    for (int i = begin; i <= end; i++) {
        printf("%d ", B[i]);
    }
    printf("\n");
    free(A);
}
