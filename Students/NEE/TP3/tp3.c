#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "mesh.h"
#include "mesh_io.h"
#include "mesh_adjacency.h"

int main(int argc, char *argv[])
{
    // Check command line arguments
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <mesh_file.obj>\n", argv[0]);
        return 1;
    }

    char *filename = argv[1];

    //  load the mesh using mesh_io functions
    struct Mesh m;
    initialize_mesh(&m);
    printf("beginning to read mesh from file\n\n");
    read_mesh_from_wavefront_file(&m, filename);
    printf("finished reading mesh from file\n\n");
    clock_t start;
    clock_t end;
    double time_seconds;
    // Now we time, remembering to skip bugatti
    if (!strstr(filename, "bugatti"))
    {
        start = clock();
        build_adjacency_table1(&m);
        end = clock();
        time_seconds = (double)(end - start) / CLOCKS_PER_SEC;
        printf("Method 1 completed in %f seconds\n\n", time_seconds);
        start = clock();
        build_adjacency_table2(&m);
        end = clock();
        time_seconds = (double)(end - start) / CLOCKS_PER_SEC;
        printf("Method 2 completed in %f seconds\n\n", time_seconds);
    }
    else
    {
        printf("Skipping method 1 and 2 \n\n");
    }
    
    start = clock();
    build_adjacency_table3(&m);
    end = clock();
    time_seconds = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Method 3 completed in %f seconds\n\n", time_seconds);

    return 0;
}