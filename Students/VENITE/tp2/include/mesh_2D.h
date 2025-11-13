#ifndef MESH2D_H
#define MESH2D_H

#include <stdio.h>

typedef struct {
    double x, y;
} Vertex2D;

typedef struct {
    int v1, v2, v3;
} Triangle;

typedef struct {
    int nv;
    Vertex2D* vert;
    int nt;
    Triangle* tri;
} Mesh2D;


int initialize_mesh2D(Mesh2D* m, int vtx_capacity, int tri_capacity);
void dispose_mesh2D(Mesh2D* m);
double area_mesh2D(const Mesh2D* m);
int read_mesh2D(Mesh2D* m, const char* filename);
int write_mesh2D(const Mesh2D* m, const char* filename);
int mesh2D_to_gnuplot(const Mesh2D* m, const char* filename);

#endif // MESH2D_H
