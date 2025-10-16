#include "mesh_2D.h"

//NOT TESTED YET

int initialize_mesh2D(struct Mesh2D *m, int vtx_capacity, int tri_capacity){
    m->nt = 0;
    m->nv = 0;
    struct Vertex *ver = malloc(sizeof(struct Vertex) * vtx_capacity);
    struct Triangle *tr = malloc(sizeof(struct Triangle) * tri_capacity);
    m->vert = ver;
    m->tri = tr;
}


void dispose_mesh2D(struct Mesh2D *m){
    m->nt = 0;
    m->nv = 0;
    free(m->vert);
    free(m->tri);
}


double area_mesh2D(struct Mesh2D *m){
    double ar = 0;
    for (int i = 0; i < m->nt; i++){
        //the coordinates
        struct Vertex a = (m->vert)[(m->tri[i]).a];
        struct Vertex b = (m->vert)[(m->tri[i]).b];
        struct Vertex c = (m->vert)[(m->tri[i]).c];

        //the two edges
        struct Vertex d1;
        d1.x = b.x - a.x;
        d1.y = b.y - a.y;

        struct Vertex d2;
        d2.x = c.x - a.x;
        d2.y = c.y - a.y;

        //cross product
        ar += 1/2 * (d1.x * d2.y - d2.x * d2.y);
    }
    return ar;
}

int read_mesh2D(struct Mesh2D* m, const char* filename){
    //read a 2D mesh from a .mesh file 
    FILE * mesh_file = fopen(filename, "r");

    char line [128]; //arbitrary number


}


int main(void) {
    return 0;
}



