#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "mesh.h"
#include "mesh_io.h"
#include "mesh_adjacency.h"

static double elapsed_ms(clock_t a, clock_t b)
{
    return 1000.0 * (double)(b - a) / CLOCKS_PER_SEC;
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "usage: %s mesh.obj\n", argv[0]);
        return 1;
    }

    struct Mesh m;
    initialize_mesh(&m);

    if (read_mesh_from_wavefront_file(&m, argv[1]) != 0)
    {
        fprintf(stderr, "could not load mesh\n");
        dispose_mesh(&m);
        return 1;
    }

    int *adj;
    clock_t t0, t1;

    if (m.ntri < 20000) // exclude bugatti for method 1
    {
        t0 = clock();
        adj = build_adjacency_table1(&m);
        t1 = clock();
        free(adj);
        printf("table1: %.2f ms\n", elapsed_ms(t0, t1));
    }

    t0 = clock();
    adj = build_adjacency_table2(&m);
    t1 = clock();
    free(adj);
    printf("table2: %.2f ms\n", elapsed_ms(t0, t1));

    t0 = clock();
    adj = build_adjacency_table3(&m);
    t1 = clock();
    free(adj);
    printf("table3: %.2f ms\n", elapsed_ms(t0, t1));

    dispose_mesh(&m);
    return 0;
}
