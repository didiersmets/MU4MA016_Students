#include "Mesh_Header.c"

#include <stdio.h>

int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <meshfile.mesh>\n", argv[0]);
        return 2;
    }

    Mesh2D m;
    /* Safe initial state: if read_mesh2D fails, dispose_mesh2D is still safe. */
    m.nv = 0; m.vert = NULL;
    m.nt = 0; m.tri  = NULL;

    if (read_mesh2D(&m, argv[1]) != 0) {
        fprintf(stderr, "Failed to read mesh: %s\n", argv[1]);
        return 1;
    }

    printf("Loaded mesh: nv=%d, nt=%d\n", m.nv, m.nt);
    printf("Signed area (sum of signed triangle areas): %.17g\n", area_mesh2D(&m));

    if (mesh2D_to_gnuplot(&m, "out.gnuplot") != 0) {
        fprintf(stderr, "Failed to write gnuplot data\n");
        dispose_mesh2D(&m);
        return 1;
    }

    if (write_mesh2D(&m, "out.mesh") != 0) {
        fprintf(stderr, "Failed to write mesh copy\n");
        dispose_mesh2D(&m);
        return 1;
    }

    printf("Wrote: out.gnuplot and out.mesh\n");

    dispose_mesh2D(&m);
    return 0;
}
