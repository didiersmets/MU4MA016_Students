#include <stddef.h> // for size_t
#include <sorting_algorithms.hpp>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>


int main(int argc, char* argv[]){
    char *filename = (char*)"sorting_results.txt";

    // open the file for writing
    FILE *fp = fopen(filename, "w");
    if (fp == NULL)
    {
        printf("Error opening the file %s", filename);
        return -1;
    }
    // write to the text file
    if(!strncmp(argv[1], "bubble", strlen("bubble"))){
        fprintf(fp, "Bubble Sort Results:\n");
    }
    if(!strncmp(argv[1], "insertion", strlen("insertion"))){
        fprintf(fp, "Insertion Sort Results:\n");
    }
    if(!strncmp(argv[1], "merge", strlen("merge"))){
        fprintf(fp, "Merge Sort Results:\n");
    }
    char a[] = "Number of elements";
    char b[] = "Time taken";
    fprintf(fp, "%s %30s\n", a, b);

    int n[7] = {10, 20, 50, 100, 200, 500, 1000};
    for(int i = 0; i < 7; i++){
        int N = n[i];
        int array[N];
        for(int j = 0; j < N; j++){
            int entry = rand();
            array[j] = entry;
        }
        if(!strncmp(argv[1], "bubble", strlen("bubble"))){
            clock_t now, after;
            double exec_time;
            now = clock();
            bubble_sort(array,N);
            after = clock();
            exec_time = ((double) (after - now)) / CLOCKS_PER_SEC;
            fprintf(fp, "%d %40f\n", N, exec_time);
            if(N < 100){
                for(int k = 0; k < N; k++){
                    fprintf(fp, "%10d", array[k]);
                    }
                fprintf(fp,"\n");
            }
        }
        if(!strncmp(argv[1], "insertion", strlen("insertion"))){
            clock_t now, after;
            double exec_time;
            now = clock();
            insertion_sort(array,N);
            after = clock();
            exec_time = ((double) (after - now)) / CLOCKS_PER_SEC;
            fprintf(fp, "%d %40f\n", N, exec_time);
        }
        if(!strncmp(argv[1], "merge", strlen("merge"))){
            clock_t now, after;
            double exec_time;
            now = clock();
            merge_sort(array,N);
            after = clock();
            exec_time = ((double) (after - now)) / CLOCKS_PER_SEC;
            fprintf(fp, "%d %40f\n", N, exec_time);
        }
    }

    // close the file
    fclose(fp);
    return 0;
}
