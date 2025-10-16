#include <stdio.h>
#include <stdlib.h>

// part 1
struct Vertex {
    // 2D space
    double x;
    double y;
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

// part 2

/* We will use INRIA mesh format : https://ljll.fr/frey/publications/RT-0253.pdf 
Example : (with reference number 0, because it's arbitrary ?)
MeshVersionFormatted 1
Dimension 2
Vertices 4
0.0 0.0 0
1.0 0.0 0
1.0 1.0 0
0.0 1.0 0
Triangles 2
0 1 2 0
0 2 3 0
End

But in the files given, beware of a space before Vertices and Triangles !
*/

int read_mesh2D(struct Mesh2D* m, const char* filename);

int mesh2D_to_gnuplot(struct Mesh2D* m, const char* filename);

int write_mesh2D(struct Mesh2D* m, const char* filename);

