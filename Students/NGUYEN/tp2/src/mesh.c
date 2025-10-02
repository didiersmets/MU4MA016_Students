#include "../include/mesh.h"

int initialize_mesh2D(struct Mesh2D* m, int vtx_capacity, int tri_capacity){

    struct Vertex *vert_init = malloc(vtx_capacity * sizeof(struct Vertex));
    struct Triangle *tri_init = malloc(tri_capacity * 3 * sizeof(struct Vertex));
    
    m->nv = vtx_capacity;
    m->vert = vert_init;
    m->nt = tri_capacity;
    m->tri = tri_init;

    return 0;
};

void dispose_mesh2D(struct Mesh2D* m); 

double area_mesh2D(struct Mesh2D* m);