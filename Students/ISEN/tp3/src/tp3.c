#include "mesh_adjacency.h"
#include "mesh_io.h"
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char* argv[]){
    if(argc != 2){
        printf("Error");
        return 0;
    }
    
    //get name of the file
    char *filename = argv[1];
    //printf("enter filename");  get why this didn't work 
    //scanf(filename);

    printf("%s\n", filename);

    struct Mesh m;
    int test = read_mesh_from_wavefront_file(&m, filename);


    //test the timings
    struct timeval chrono;

    /*timer_start(&chrono);
    int *adj1 = build_adjacency_table1(&m);
    unsigned int first = timer_stop(&chrono, "1");*/

    /*timer_start(&chrono);
    int *adj2= build_adjacency_table2(&m);
    unsigned int second = timer_stop(&chrono, "2");*/

    timer_start(&chrono);
    int *adj3 = build_adjacency_table3(&m);
    unsigned int third = timer_stop(&chrono, "3");

    printf("Test");


    //check if same adjacency table for each algo
    /*
    for (int i = 0; i < 3 * m.ntri; i ++){
        if(adj1[i] != adj2[i] || adj1[i] != adj3[i]){
            printf("Problem, algo not correct");
            return 0;
        }
    }
    printf("algo correct");*/
    return 0;
}
