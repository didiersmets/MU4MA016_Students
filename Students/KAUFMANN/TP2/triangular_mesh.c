#include <stdlib.h>

struct Vertex {
    double x_coord;
    double y_coord;
    double z_coord;
}

struct Triangle {
    int a;
    int b;
    int c;
}

struct Mesh2D {
    int nv;
    struct Vertex *vert;
    int nt;
    struct Triangle *tri;
}

int initialize_mesh2D(struct Mesh2D *m, int vtx_capacity, int tri_capacity) {
    m->vert = (struct Vertex *)malloc(vtx_capacity*sizeof(struct Vertex));
    m->tri = (struct Triangle *)malloc(tri_capacity*sizeof(struct Triangle));
    m->nv = vtx_capacity;
    m->nt = tri_capacity;
}

void dispose_mesh2D(struct Mesh2D *m) {
    free(m->vert);
    free(m->tri);
    m->nv = 0;
    m->nt = 0;
}

double area_mesh2D(struct Mesh2D *m) {
    for (int i = 0; i < mesh->nt; i++) {
        double total_area = 0;
        Triangle t = m->tri[i];
        Vertex v1 = m->vert[t->a];
        Vertex v2 = m->vert[t->b];
        Vertex v3 = m->vert[t->c];
        double area = 0.5 * (v1->coord_x*(v2->coord_y - v3->coord_y) + v2->coord_x*(v3->coord_y - v1->coord_y) +
        v3->coord_x*(v1->coord_y - v2->coord_y));
        total_area += area;
    
    return total_area;
    }
}

double area_mesh3D(struct Mesh2D *m) {
    for (int i = 0; i < mesh->nt; i++) {
        double total_area = 0;
        Triangle t = m->tri[i];
        Vertex v1 = m->vert[t->a];
        Vertex v2 = m->vert[t->b];
        Vertex v3 = m->vert[t->c];
        double b_x = (v1->coord_x+v2->coord_x+v3->coord_x)/3;
        double b_y = (v1->coord_y+v2->coord_y+v3->coord_y)/3;
        double b_z = (v1->coord_z+v2->coord_z+v3->coord_z)/3;
        