#include "../include/mesh.h"
#include <math.h>

int initialize_mesh2D(struct Mesh2D* m, int vtx_capacity, int tri_capacity){

    struct Vertex *vert_init = malloc(vtx_capacity * sizeof(struct Vertex));
    struct Triangle *tri_init = malloc(tri_capacity * sizeof(struct Triangle));
    
    m->nv = vtx_capacity;
    m->vert = vert_init;
    m->nt = tri_capacity;
    m->tri = tri_init;

    return 0;
};

void dispose_mesh2D(struct Mesh2D* m){
    free(m->vert);
    free(m->tri);
    free(m);
    return;
}; 

// question 5

static double euclidean_norm_vertex(struct Vertex *a){
    return sqrt(pow((a->x[0] - a->y[0]), 2) + pow((a->x[1] - a->y[1]), 2));
};

static double area_triangle_heron(struct Vertex *v1, struct Vertex *v2, struct Vertex *v3){
    double v1_norm = euclidean_norm_vertex(v1);
    double v2_norm = euclidean_norm_vertex(v2);
    double v3_norm = euclidean_norm_vertex(v3);
    double semi_perimeter = (double)(v1_norm + v2_norm + v3_norm)/2;
    return sqrt(semi_perimeter * (semi_perimeter - v1_norm) * (semi_perimeter - v2_norm) * (semi_perimeter - v3_norm));
};

double area_mesh2D(struct Mesh2D* m){
    /* returns the signed area of a mesh ;
    - assuming a manifold mesh (in the intersection between two triangle, only common vertice, meaning vertice for both, or common edges)
    - assuming all triangles have the same orientation (so that a shared vertice between two triangles have the two orientations "go both ways")
    */

    // we can choose Heron's formula to compute the area of a triangle, needing only the lenght of the vertices
    // choosing euclidean norm
    double area_sum_triangles = 0.0;
    for (int i = 0; i < m->nt; i++){
        struct Vertex *v1 = m->vert[0];
        struct Vextex *
        area_sum_triangles += area_triangle_heron(v1, v2, v3);
    }
    return area_sum_triangles;

};