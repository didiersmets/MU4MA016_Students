#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Vertex
{
    long double x;
    long double y;
};

struct Triangle
{
    int v1;     //index of first vertex
    int v2;     //index of second vertex
    int v3;     //index of third vertex
};

struct Mesh2D
{
    size_t nv;              //number of vertices
    struct Vertex* vert;    //actual vertices
    size_t nt;              //number of triangles
    struct Triangle* tri;   //actual triangles
};

int initialize_mesh2D(struct Mesh2D* m, int vxt_capacity, int tri_capacity);
void dispose_mesh2D(struct Mesh2D* m);
double area_mesh2D(struct Mesh2D* m);
int read_mesh2D(struct Mesh2D* m, const char* filename);
int mesh2D_to_gnuplot(struct Mesh2D* m, const char* filename);
int write_mesh2D(struct Mesh2D* m, const char* filename);