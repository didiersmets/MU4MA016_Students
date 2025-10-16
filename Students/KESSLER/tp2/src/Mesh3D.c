#include "Mesh3D.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int initialize_mesh3D(struct Mesh3D* m, int vert_capacity, int tri_capacity) {
    m->nv = 0;
    m->nt = 0;

    m->vertices = (struct Vertex3D*) malloc(sizeof(struct Vertex3D) * vert_capacity);
    m->triangles = (struct Triangle3D*) malloc(sizeof(struct Triangle3D) * tri_capacity);

    return 0;
}

int dispose_mesh3D(struct Mesh3D* m) {
    free(m->vertices);
    m->vertices = NULL;
    
    free(m->triangles);
    m->triangles = NULL;

    return 0;
}

double volume_mesh3D(struct Mesh3D* m) {
    double volume = 0.0;

    for (int i = 0; i < m->nt; i++) {
        // Initialization
        struct Triangle3D tri = m->triangles[i];
        struct Vertex3D a = m->vertices[tri.v1];
        struct Vertex3D b = m->vertices[tri.v2];
        struct Vertex3D c = m->vertices[tri.v3];

        // Barycenter g = (a+b+c)/3
        struct Vertex3D barycenter;
        barycenter.x = (a.x + b.x + c.x) / 3.0;
        barycenter.y = (a.y + b.y + c.y) / 3.0;
        barycenter.z = (a.z + b.z + c.z) / 3.0;

        // Normal vector n = (b-a) x (c-a)
        double abx = b.x - a.x;
        double aby = b.y - a.y;
        double abz = b.z - a.z;

        double acx = c.x - a.x;
        double acy = c.y - a.y;
        double acz = c.z - a.z;

        struct Vertex3D normal;
        normal.x = aby * acz - abz * acy;
        normal.y = abz * acx - abx * acz;
        normal.z = abx * acy - aby * acx;

        // Scalar product normal x barycenter
        volume += normal.x * barycenter.x + normal.y * barycenter.y + normal.z * barycenter.z;
    }

    return volume / 6.0;
}