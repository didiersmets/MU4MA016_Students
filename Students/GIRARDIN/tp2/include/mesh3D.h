#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Vertex3D
{
    long double x;
    long double y;
    long double z;
};

struct Triangle3D
{
    int v1;     //index of first vertex
    int v2;     //index of second vertex
    int v3;     //index of third vertex
};

struct Mesh3D
{
    size_t nv;                  //number of vertices
    struct Vertex3D* vert;      //actual vertices
    size_t nt;                  //number of triangles
    struct Triangle3D* tri;     //actual triangles
};

int initialize_mesh3D(struct Mesh3D* m, int vxt_capacity, int tri_capacity);
void dispose_mesh3D(struct Mesh3D* m);
double volume_mesh3D(struct Mesh3D* m);
int read_mesh3D(struct Mesh3D* m, const char* filename);
int mesh3D_to_gnuplot(struct Mesh3D* m, const char* filename);
int write_mesh3D(struct Mesh3D* m, const char* filename);