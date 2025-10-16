#include "../include/mesh.h"
#include <stdio.h>

int main() {
    struct Mesh2D *m;
    //initialize_mesh2D(m, 10, 10);
    read_mesh2D(m, "../mesh1-tp2_2D.mesh");
    mesh2D_to_gnuplot(m, "mesh.dat");
    //dispose_mesh2D(m);
    printf("GNUplot data file 'mesh.dat' generated successfully.\n");
    return 0;
}

