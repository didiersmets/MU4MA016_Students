#include "mesh_3D.h"

//NOT TESTED YET

int initialize_mesh3D(struct Mesh3D *m, int vtx_capacity, int tri_capacity){
    m->nt = 0;
    m->nv = 0;
    struct Vertex *ver = malloc(sizeof(struct Vertex) * vtx_capacity);
    struct Triangle *tr = malloc(sizeof(struct Triangle) * tri_capacity);
    m->vert = ver;
    m->tri = tr;
}


void dispose_mesh3D(struct Mesh3D *m){
    m->nt = 0;
    m->nv = 0;
    free(m->vert);
    free(m->tri);
}


double volume3D(struct Mesh3D *m){
    double vol = 0;
    double ar = 0;
    for (int i = 0; i < m->nt; i++){
        //the coordinates
        struct Vertex a = (m->vert)[(m->tri[i]).a];
        struct Vertex b = (m->vert)[(m->tri[i]).b];
        struct Vertex c = (m->vert)[(m->tri[i]).c];

        //the two edges
        struct Vertex d1;  //ab
        d1.x = b.x - a.x;   
        d1.y = b.y - a.y;
        d1.z = b.z - b.z;

        struct Vertex d2;  //ac
        d2.x = c.x - a.x;
        d2.y = c.y - a.y;
        d2.z = c.z - a.z;

        //cross product for normal vector
        struct Vertex n;
        n.x = d1.y * d2.z - d1.z * d2.y;
        n.y = d1.z * d2.x - d1.x - d2.z;
        n.z = d1.x * d2.y - d1.y * d2.x;

        //barycenter
        struct Vertex bary;
        bary.x = (a.x + b.x + c.x)/3;
        bary.y = (a.y + b.y + c.y)/3;
        bary.z = (a.z + b.z + c.z)/3;

        //area of triangle
        ar = 1/2 * sqrt(n.x * n.x + n.y * n.y + n.z * n.z);

        //formula for volume
        vol += (bary.x * n.x + bary.y * n.y + bary.z * n.z) * ar;
    }
    return (1/3 * vol);
}


int main(void) {
    return 0;
}