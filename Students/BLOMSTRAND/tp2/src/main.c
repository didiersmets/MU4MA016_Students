#include <stdio.h>
#include "mesh.h"

int main()
{
    struct Mesh2D m;

    if (read_mesh2D(&m, "mesh2-tp2.mesh") != 0)
    {
        printf("Error loading mesh\n");
        return 1;
    }

    double A = area_mesh2D(&m);
    printf("Total area = %lf\n", A);

    mesh2D_to_gnuplot(&m, "plot.dat");

    write_mesh2D(&m, "output.mesh");

    dispose_mesh2D(&m);

    return 0;
}
