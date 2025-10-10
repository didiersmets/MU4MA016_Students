#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct Vertex{
    double x;
    double y;
};

struct Triangle{
    int a;   //or v[1], v[2], v[3]
    int b;
    int c;
};

struct Mesh2D{
    int nv;
    struct Vertex *vert;
    int nt;
    struct Triangle *tri;
};

void dispose_mesh2D(struct Mesh2D* m);


double area_mesh2D(struct Mesh2D* m);
