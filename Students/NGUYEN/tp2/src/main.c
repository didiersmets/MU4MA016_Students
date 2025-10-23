#include "../include/mesh.h"
#include <stdio.h>

int main() {

    struct Mesh2D m; // and not *m...
    initialize_mesh2D(&m, 10, 10);
    read_mesh2D(&m, "../mesh1-tp2_2D.mesh");
    
    mesh2D_to_gnuplot(&m, "../mesh.dat");
    printf("mesh.dat generated\n");
    printf("to generate a \"mesh.png\", run gnuplot\n");
    /* in gnuplot :
    set style fill solid
    plot "../mesh.dat" with polygons lc rgb "blue" title "Mesh"
    set terminal png
    set output "../mesh.png"
    replot
    */
    dispose_mesh2D(&m);
    
    return 0;
}

