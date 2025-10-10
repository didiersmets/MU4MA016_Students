#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../include/hashtable.h"
#include "../include/mesh.h"
#include "../include/mesh_io.h"

int main(int argc, char **argv){
    char *filename = argv[1];
    struct Mesh m;

    read_mesh_from_wavefront_file(&m, filename);

    time_t before1 = time(NULL);
    int *adj1 = build_adjacency_table1(&m);
    time_t after1 = time(NULL);
    printf("Time of the first algorithm : %lds\n", after1 - before1);

    time_t before2 = time(NULL);
    int *adj2 = build_adjacency_table2(&m);
    time_t after2 = time(NULL);
    printf("Time of the second algorithm : %lds\n", after2 - before2);

    time_t before3 = time(NULL);
    int *adj3 = build_adjacency_table3(&m);
    time_t after3 = time(NULL);
    printf("Time of the third algorithm : %lds\n", after3 - before3);

    free(adj1);
    free(adj2);
    free(adj3);

    return 0;
}