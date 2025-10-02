#include "sorting.h"

//n = number of elements in the array
void bubble_sort(int *arr, int n){
    int st;
    for (int i = 0; i < n-1; i++){
        for (int j = 0; j < n-i-1; j++){
            if(arr[j] > arr[j+1]){
                st = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = st;
            }
        }
    }
}

void insertion_sort(int *arr, int n){
    int st;
    for (int i = 1; i < n; i++){
        int j = i;
        while(arr[j] < arr[j-1] && j>0){
            st = arr[j];
            arr[j] = arr[j-1];
            arr[j-1] = st;
            j--;
        }
    }
}

