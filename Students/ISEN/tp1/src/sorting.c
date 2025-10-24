#include "sorting.h"
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h> //memcpy

//missing: in-place merge sort

//finally not used, but test if array is well-sorted
bool is_sorted(int *arr, int length){
    for (int i = 0; i < length-1; i++){
        if(arr[i] > arr[i+1]){
            return(0);
        }
    }
    return(1);
}

//prints out array --> used to see if array is sorted
void print_arr(int *arr, int length){
    for(int i = 0; i < length; i++){
        printf("%d\t", arr[i]);
    }
    printf("\n");
}

int main(){
    //create file to record execution time (finally only the last one is used)
    FILE *bubble_time;  
    bubble_time = fopen("bubble_time.txt", "w"); /*w = writing mode*/

    FILE *insertion_time;  
    insertion_time = fopen("insertion_time.txt", "w"); /*w = writing mode*/

    FILE *merge_time;  
    merge_time = fopen("merge_time.txt", "w"); /*w = writing mode*/

    FILE *all_time;
    all_time = fopen("all_time.txt", "w"); /*w = writing mode*/

    struct timeval chrono;

    int N[] = {10,20,50,100,200,500,1000};  //different lengths of the arrays
    for (int i=0; i<7;i++){
        int *T = (int *)malloc(N[i] * sizeof(int));
        srand(time(NULL));
        for (int j = 0; j < N[i]; j++){
            T[j] = rand();
        }

        //copy array T into temporary arrays for each algo, otherwise no sorting needed after bubble sort 
        int *B = (int *)malloc(N[i] * sizeof(int));
        int *I = (int *)malloc(N[i] * sizeof(int));
        int *M = (int *)malloc(N[i] * sizeof(int));

        memcpy(B, T, N[i] * sizeof(int));
        memcpy(I, T, N[i] * sizeof(int));
        memcpy(M, T, N[i] * sizeof(int));
        
        //start sorting algos & time measuring 
        timer_start(&chrono);
        bubble_sort(B, N[i]);
        unsigned int b = timer_stop(&chrono, "Bubble");

        timer_start(&chrono);
        insertion_sort(I, N[i]);
        unsigned int in = timer_stop(&chrono, "Insertion");

        timer_start(&chrono);
        merge_sort(M, 0, N[i]-1);
        unsigned int m = timer_stop(&chrono, "Merge");

        //write times into files 
        fprintf(bubble_time, "%d\t%d\n", N[i], b); /*write text into file, tab & linkebreak*/
        fprintf(insertion_time, "%d\t%d\n", N[i], in);
        fprintf(merge_time, "%d\t%d\n", N[i], m);
        fprintf(all_time, "%d\t%d\t%d\t%d\n", N[i], b, in, m);

        //quick check if algos seem to work well
        if(N[i]<=20){
            print_arr(T, N[i]);
            printf("Bubble\n");
            print_arr(B, N[i]);
            printf("Insertion\n");
            print_arr(I, N[i]);
            printf("Merge\n");
            print_arr(M, N[i]);
        }

        free(T);
        free(B);
        free(I);
        free(M);
    }
    fclose(bubble_time);
    fclose(insertion_time); 
    fclose(merge_time); 
    fclose(all_time);

    //for plot: first put code into file, then read this file 
    FILE *gnu;
    gnu = fopen("gnu.txt", "w"); /*w = writing mode*/      
    fprintf(gnu, "set title 'Comparison execution time'\n"
        "set xlabel 'nb elements'\n" 
        "set ylabel 'time (ms)'\n"
        "set grid\n"
        "set logscale x\n" 
        "set logscale y\n" 
        "plot 'all_time.txt' using 1:2 with linespoints title 'bubble',"
        " 'all_time.txt' using 1:3 w linespoints title 'insertion',"
        " 'all_time.txt' using 1:4  w linespoints title 'merge'"
        );
    fclose(gnu);
    system("gnuplot -p gnu.txt");
}



//to compile: gcc sorting.c bubble_insertion_sort.c merge_sort.c chrono.c -I include -o sorting