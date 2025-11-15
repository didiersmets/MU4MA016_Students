#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>


/* 1) Point in 2D-plane */
typedef struct {
    double x;   /* x-koordinat */
    double y;   /* y-koordinat */
} Vertex;

/* 2) Triangle */

typedef struct Traingle {
    Vertex v1;  /* Första hörnet */
    Vertex v2;  /* Andra hörnet */
    Vertex v3;  /* Tredje hörnet */
} Triangle;

/* 3) 2D triangle mesh */
typedef struct Mesh2D {
    int      nv;    /*nv = nr of vertex*/
    Vertex  *vert;  

    int       nt;   /*nt = nr of triangles*/
    Triangle *tri;  
} Mesh2D;

/* 4)  */

int initialize_mesh2D(struct Mesh2D* m, int vtx_capacity, int tri_capacity) {
    if (!m || vtx_capacity < 0 || tri_capacity < 0) return -1;

    m->nv  = 0; /*nv = nr of vertex*/
    m->nt  = 0; /*nt = nr of triangles*/
    m->vert = NULL;
    m->tri  = NULL;

    if (vtx_capacity > 0) {
        m->vert = (Vertex*)malloc((size_t)vtx_capacity * sizeof(Vertex));
        if (!m->vert) return -1;
    }
    if (tri_capacity > 0) {
        m->tri = (Triangle*)malloc((size_t)tri_capacity * sizeof(Triangle));
        if (!m->tri) { free(m->vert); m->vert = NULL; return -1; }
    }
    return 0;  
}


void dispose_mesh2D(struct Mesh2D* m) {
    if (!m) return;
    free(m->tri);
    free(m->vert);
    m->tri  = NULL;
    m->vert = NULL;
    m->nt = 0;
    m->nv = 0;

}

/* 5) Compute signed area of mesh */
double area_mesh2D(struct Mesh2D* m) {
    if (!m || !m->tri || m->nt <= 0) return 0.0;

    double A = 0.0;
    for (int i = 0; i < m->nt; ++i) {
        const Vertex a = m->tri[i].v1;
        const Vertex b = m->tri[i].v2;
        const Vertex c = m->tri[i].v3;

        /* Signed area of triangle (a,b,c):
           0.5 * ((bx-ax)*(cy-ay) - (cx-ax)*(by-ay)) */
        const double abx = b.x - a.x;
        const double aby = b.y - a.y;
        const double acx = c.x - a.x;
        const double acy = c.y - a.y;

        A += 0.5 * (abx * acy - acx * aby);
    }
    return A;
}



/* 6)  */

/*2. Reading, writing and visualizing a mesh*/

int read_mesh2d(struct Mesh2D* m, const char* filename) {
    
}



