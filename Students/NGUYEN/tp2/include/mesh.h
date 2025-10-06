#include <stdio.h>
#include <stdlib.h>

struct Vertex {
    // 2D space
    double x[2];
    double y[2];
};

struct Triangle {
    int Index[3]; // its vertices are given through an index (array of int, size 3)
};

struct Mesh2D {
    int nv; // number of vertices
    struct Vertex *vert; // where the vertices are
    int nt; // number of triangles
    struct Triangle *tri; // where the triangles are 
};

int initialize_mesh2D(struct Mesh2D* m, int vtx_capacity, int tri_capacity);

void dispose_mesh2D(struct Mesh2D* m); 

double area_mesh2D(struct Mesh2D* m);

