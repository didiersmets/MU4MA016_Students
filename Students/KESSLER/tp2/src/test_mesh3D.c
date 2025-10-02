#include "Mesh3D.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int main() {
    struct Mesh3D mesh;
    if (initialize_mesh3D(&mesh, 10, 5) != 0) {
        // Handle initialization error
        return 1;
    }

    // Add vertices
    mesh.vertices[0].x = 1.0; mesh.vertices[0].y = 1.0; mesh.vertices[0].z = 1.0;
    mesh.vertices[1].x = 3.0; mesh.vertices[1].y = 4.0; mesh.vertices[1].z = 3.0;
    mesh.vertices[2].x = 5.0; mesh.vertices[2].y = 2.0; mesh.vertices[2].z = 5.0;
    mesh.vertices[3].x = 2.0; mesh.vertices[3].y = 3.0; mesh.vertices[3].z = 4.0;
    mesh.nv = 4;

    // Add triangles
    mesh.triangles[0].v1 = 0; mesh.triangles[0].v2 = 1; mesh.triangles[0].v3 = 2;
    mesh.triangles[1].v1 = 0; mesh.triangles[1].v2 = 2; mesh.triangles[1].v3 = 3;
    mesh.triangles[2].v1 = 0; mesh.triangles[2].v2 = 3; mesh.triangles[2].v3 = 1;
    mesh.triangles[3].v1 = 3; mesh.triangles[3].v2 = 2; mesh.triangles[3].v3 = 1;
    mesh.nt = 4;

    double volume = volume_mesh3D(&mesh);
    printf("Calculated Volume: %lf\n", volume);

    dispose_mesh3D(&mesh);
    return 0;
}