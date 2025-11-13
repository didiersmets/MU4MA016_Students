#include <stdlib.h>
#include <stdio.h>
#include <math.h>


struct Vertex{
    double x;
    double y;
    double z;
};

struct Triangle{
    int a;   //or v[1], v[2], v[3]
    int b;
    int c;
};

struct Mesh3D{
    int nv;
    struct Vertex *vert;
    int nt;
    struct Triangle *tri;
};

void dispose_mesh3D(struct Mesh3D* m);


double area_mesh3D(struct Mesh3D* m);

