#ifndef MESH3D_H
#define MESH3D_H

#include <stdio.h>


typedef struct {
    double x, y, z;
} Vertex3D;

typedef struct {
    int v1, v2, v3;
} Triangle3D;


typedef struct {
    int nv;
    Vertex3D* vert;
    int nt;
    Triangle3D* tri;
} Mesh3D;

int initialize_mesh3D(Mesh3D* m, int vtx_capacity, int tri_capacity);
void dispose_mesh3D(Mesh3D* m);
double volume_mesh3D(const Mesh3D* m);
int read_mesh3D(Mesh3D* m, const char* filename);
int write_mesh3D(const Mesh3D* m, const char* filename);

#endif // MESH3D_H
