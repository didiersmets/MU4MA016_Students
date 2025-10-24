#include "Mesh2D.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    struct Mesh2D mesh;
    
    // Test initialization
    printf("Testing mesh initialization...\n");
    if (initialize_mesh2D(&mesh, 5, 4) != 0) {
        printf("Failed to initialize mesh\n");
        return 1;
    }
    printf("Mesh initialized successfully\n\n");

    // Test reading from file
    printf("Testing mesh reading from file...\n");
    if (read_mesh2D(&mesh, "mesh1-tp2.mesh") != 0) {
        printf("Failed to read mesh from file\n");
        return 1;
    }
    printf("Successfully read mesh with %d vertices and %d triangles\n\n", 
           mesh.nv, mesh.nt);

    // Print mesh data for verification
    printf("Mesh vertices:\n");
    for (int i = 0; i < mesh.nv; i++) {
        printf("Vertex %d: (%.2f, %.2f)\n", i, mesh.vertices[i].x, mesh.vertices[i].y);
    }
    printf("\nMesh triangles:\n");
    for (int i = 0; i < mesh.nt; i++) {
        printf("Triangle %d: %d-%d-%d\n", i, 
               mesh.triangles[i].v1, mesh.triangles[i].v2, mesh.triangles[i].v3);
    }
    printf("\n");

    // Test writing to gnuplot format
    printf("Testing gnuplot output...\n");
    if (mesh2D_to_gnuplot(&mesh, "mesh_plot.gnu") != 0) {
        printf("Failed to write gnuplot file\n");
        return 1;
    }
    printf("Successfully wrote gnuplot file\n\n");

    // Test writing mesh to file
    printf("Testing mesh writing to file...\n");
    if (write_mesh2D(&mesh, "mesh_output.mesh") != 0) {
        printf("Failed to write mesh to file\n");
        return 1;
    }
    printf("Successfully wrote mesh to file\n\n");

    // Test disposal
    printf("Testing mesh disposal...\n");
    if (dispose_mesh2D(&mesh) != 0) {
        printf("Failed to dispose mesh\n");
        return 1;
    }
    printf("Successfully disposed mesh\n");

    return 0;
}