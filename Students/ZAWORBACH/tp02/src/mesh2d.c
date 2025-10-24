#include "../include/vertex.h"
#include "../include/triangle.h"
#include "../include/mesh2d.h"

#include <stdlib.h> // for malloc, free
#include <string.h> // for memset

int *mesh2d_init(struct mesh2d *m, size_t vtx_capacity, size_t tri_capacity) {

    m->nv = vtx_capacity;
    m->vert = malloc(vtx_capacity * sizeof(struct Vertex));
    if (m->vert == NULL) {
        return NULL; // Memory allocation failed
    }

    m->nt = 0;
    m->tri = malloc(tri_capacity * sizeof(struct Triangle));
    if (m->tri == NULL) {
        free(m->vert);
        m->vert = NULL;
        return NULL; // Memory allocation failed
    }

    return (int[]){(int)vtx_capacity, (int)tri_capacity}; // Return capacities as an array
}