#include <stdbool.h>
#include <stddef.h> // for size_t

struct mesh2d {
    int nv; // number of vertices
    struct Vertex *vert; 
    int nt; // number of triangles
    struct Triangle *tri;
};

int *mesh2d_init(struct mesh2d *m, size_t vtx_capacity, size_t tri_capacity);
void mesh2d_dispose(struct mesh2d *m);
double area_mesh2d(const struct mesh2d *m);
