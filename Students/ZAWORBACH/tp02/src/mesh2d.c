#include "../include/vertex.h"
#include "../include/triangle.h"
#include "../include/mesh2d.h"

#include <stdlib.h> // for malloc, free
#include <string.h> // for memset
#include <math.h>
#include <stdio.h>

int mesh2d_init(struct mesh2d *m, size_t vtx_capacity, size_t tri_capacity) {

    if (m == NULL)
    {
        return -1;
    }
    m->nv = 0;
    m->nt = 0;
    m->vert = malloc(vtx_capacity * sizeof(struct Vertex));
    if (m->vert == NULL) {
        return NULL; 
    }

    m->tri = malloc(tri_capacity * sizeof(struct Triangle));
    if (m->tri == NULL) {
        free(m->vert);
        m->vert = NULL;
        return NULL; 
    }
    return 0; 

}

void mesh2d_dispose(struct mesh2d *m)
{
    if (m == NULL) {
        return;
    }
    
    free(m->vert);
    m->vert = NULL;
    
    free(m->tri);
    m->tri = NULL;
    
    m->nv = 0;
    m->nt = 0;
}
static double triangle_area (const struct Triangle *t)
{
    const struct Vertex *v1 = t->v1;
    const struct Vertex *v2 = t->v2;
    const struct Vertex *v3 = t->v3;

    double dx1 = v2->x - v1->x;
    double dy1 = v2->y - v1->y;
    double dx2 = v3->x - v1->x;
    double dy2 = v3->y - v1->y;
    
    double cross = dx1 * dy2 - dx2 * dy1;
    
    return 0.5 * fabs(cross);

}
double area_mesh2d(const struct mesh2d *m)
{
    if (m == NULL)
    {
        return 0.0;
    }

    double total_area = 0.0;
    for (int i=0; i < m->nt; i++)
    {
        total_area += triangle_area((struct Triangle *)((char *) m->tri + i * sizeof(struct Triangle)));
    }

    return total_area;
}

int read_mesh2d(struct mesh2d* m, const char* filename){
    // Read .mesh file 

    FILE *file = fopen(filename, "r");
    if (file == NULL) {return -1;}
     char buffer [128];
     
    while (fgets(buffer, sizeof(buffer), file)) {
        if (sscanf(buffer, "Vertices %d", &m->nv) == 1) {
            break;
        }
    }
    for (int i=0; i<m->nv; i++){
        double x, y;
        fscanf(buffer, "%f %f", &x, &y);
        m->vert[i].x = x;
        m->vert[i].y = y;
    }
    
    while (fgets(buffer, sizeof(buffer), file)) {
        if (fscanf(file, "Triangles %d", &m->nt) == 1) {
            break;
        }
    }
    for (int i=0; i<m->nt; i++){
        int v1,v2,v3;
        fscanf(file, "%d %d %d", &v1, &v2, &v3);
        m->tri[i].v1 = v1 - 1;
        m->tri[i].v2 = v2 - 1;
        m->tri[i].v3 = v3 - 1;

    }
    fclose(file);

}

int write_mesh2d(const struct mesh2d* m, const char* filename){
    // Write .mesh file 

    FILE *file = fopen(filename, "w");
    if (file == NULL) {return -1;}
    
    fprintf(file, "MeshVersionFormatted 1\n");
    fprintf(file, "Dimension 2\n");
    fprintf(file, "Vertices %d\n", m->nv);
    for (int i=0; i<m->nv; i++){
        fprintf(file, "%f %f 0\n", m->vert[i].x, m->vert[i].y);
    }
    fprintf(file, "Triangles %d\n", m->nt);
    for (int i=0; i<m->nt; i++){
        fprintf(file, "%d %d %d 0\n", m->tri[i].v1 + 1, m->tri[i].v2 + 1, m->tri[i].v3 + 1);
    }
    fprintf(file, "End\n");
    fclose(file);
    fprintf("Mesh written to %s\n", filename);
    return 0;

}

