#include <stddef.h> // for size_t
#include <mesh.h>
#include <mesh_adjacency.h>
#include <mesh_io.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

int main(int argc, char* argv[]){
    //printf("Hello World\n");
    char* filename1 = argv[1];
    printf("Filename: %s\n", argv[1]);
    struct Mesh *m = (struct Mesh*) malloc(sizeof(struct Mesh));
    read_mesh_from_wavefront_file(m, filename1);
    //printf("After Reading\n");
    clock_t now, after;
    double exec_time;
    //printf("Aftert clocks initial\n");
    int* adj1;
    int* adj2;
    int* adj3;
    //printf("After adjTables initial\n");
    if(strncmp(argv[1], "bugatti.obj", strlen("bugatti.obj"))){
        now = clock();
        adj1 = build_adjacency_table1(m);
        after = clock();
        exec_time = ((double) (after - now)) / CLOCKS_PER_SEC;
        printf("Adj. %d %40f\n", 1, exec_time);
    }
    now = clock();
    adj2 = build_adjacency_table2(m);
    after = clock();
    exec_time = ((double) (after - now)) / CLOCKS_PER_SEC;
    printf("Adj. %d %40f\n", 2, exec_time);
    now = clock();
    adj3 = build_adjacency_table3(m);
    after = clock();
    exec_time = ((double) (after - now)) / CLOCKS_PER_SEC;
    printf("Adj. %d %40f\n", 3, exec_time);
    char *outputfile = (char*)"sorting_results.txt";
    // open the file for writing
    FILE *fp = fopen(outputfile, "w");
    if (fp == NULL)
    {
        printf("Error opening the file %s", outputfile);
        return -1;
    }
    // write to the text file
    fprintf(fp, "Adj Table 1 Results:\n");
    //char a[] = "Number of elements";
    //char b[] = "Time taken";
    //fprintf(fp, "%s %30s\n", a, b);
    if(strncmp(argv[1], "bugatti.obj", strlen("bugatti.obj"))){
        for(int i = 0; i < m->ntri; i++){
            fprintf(fp, "%d %10d %20d \n", adj1[3*i], adj1[3*i+1], adj1[3*i+2]);
        }
    }
    fprintf(fp, "\n Adj Table 2 Results:\n");
    for(int i = 0; i < m->ntri; i++){
        fprintf(fp, "%d %10d %20d \n", adj2[3*i], adj2[3*i+1], adj2[3*i+2]);
    }
    fprintf(fp, "\n Adj Table 3 Results:\n");
    for(int i = 0; i < m->ntri; i++){
        fprintf(fp, "%d %10d %20d \n", adj3[3*i], adj3[3*i+1], adj3[3*i+2]);
    }
    /*
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
    */
    // close the file
    fclose(fp);

    dispose_mesh(m);
    return 0;
}




