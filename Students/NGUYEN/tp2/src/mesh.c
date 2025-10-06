#include "../include/mesh.h"
#include <math.h>
#include <string.h>

int initialize_mesh2D(struct Mesh2D* m, int vtx_capacity, int tri_capacity){

    struct Vertex *vert_init = malloc(vtx_capacity * sizeof(struct Vertex));
    struct Triangle *tri_init = malloc(tri_capacity * sizeof(struct Triangle));
    
    m->nv = vtx_capacity;
    m->vert = vert_init;
    m->nt = tri_capacity;
    m->tri = tri_init;

    return 0;
}

void dispose_mesh2D(struct Mesh2D* m){
    free(m->vert);
    free(m->tri);
    //free(m);
    return;
}

// question 5

static double distance(struct Vertex *a, struct Vertex *b) {
    double dx = a->x - b->x;
    double dy = a->y - b->y;
    return sqrt(dx*dx + dy*dy);
}

static double area_triangle_heron(struct Vertex *v1, struct Vertex *v2, struct Vertex *v3) {
    double a = distance(v1, v2);
    double b = distance(v2, v3);
    double c = distance(v3, v1);
    double s = (a + b + c) / 2.0;
    return sqrt(s * (s - a) * (s - b) * (s - c));
}

double area_mesh2D(struct Mesh2D* m){
    /* returns the signed area of a mesh ;
    - assuming a manifold mesh (in the intersection between two triangle, only common vertice, meaning vertice for both, or common edges)
    - assuming all triangles have the same orientation (so that a shared vertice between two triangles have the two orientations "go both ways")
    */

    // we can choose Heron's formula to compute the area of a triangle, needing only the lenght of the vertices
    // suggestion for a better code : using a scalar product

    double area_sum = 0.0;
    for (int i = 0; i < m->nt; i++) {
        struct Vertex *v1 = &m->vert[m->tri[i].Index[0]];
        struct Vertex *v2 = &m->vert[m->tri[i].Index[1]];
        struct Vertex *v3 = &m->vert[m->tri[i].Index[2]];
        area_sum += area_triangle_heron(v1, v2, v3);
    }
    return area_sum;
}

/*
int read_mesh2D(struct Mesh2D* m, const char* filename) {
    FILE* fp = fopen(filename, "r");
    if (!fp) return EXIT_FAILURE;

    char line[256];
    int nv, nt;
    int found_vertices = 0, found_triangles = 0;

    while (fgets(line, sizeof(line), fp)) {
        if (strstr(line, "MeshVersionFormatted")) continue;
        if (strstr(line, "Dimension 2")) continue;
        if (strstr(line, "Vertices")) {
            if (fscanf(fp, "%d", &nv) != 1) { 
            fclose(fp); 
            return EXIT_FAILURE; 
            }
            if (initialize_mesh2D(m, nv, 0) != 0) { 
            fclose(fp); 
            return EXIT_FAILURE; 
            }
            for (int i = 0; i < nv; i++) {
                if (fscanf(fp, "%lf %lf", &m->vert[i].x, &m->vert[i].y) != 2) {
                    fclose(fp);
                    return EXIT_FAILURE;
                }
                // Ignore ref and optional attributes
                while (fgetc(fp) != '\n' && !feof(fp));
            }
            found_vertices = 1;
        }
        if (strstr(line, "Triangles")) {
            if (fscanf(fp, "%d", &nt) != 1) {
            fclose(fp); 
            return EXIT_FAILURE; 
            }
            if (initialize_mesh2D(m, m->nv, nt) != 0) { 
            fclose(fp); 
            return EXIT_FAILURE; 
            }
            for (int i = 0; i < nt; i++) {
                if (fscanf(fp, "%d %d %d",
                    &m->tri[i].Index[0],
                    &m->tri[i].Index[1],
                    &m->tri[i].Index[2]) != 3) {
                    fclose(fp);
                    return EXIT_FAILURE;
                }
                // Ignore ref and optional attributes
                while (fgetc(fp) != '\n' && !feof(fp));
            }
            m->nt = nt;
            found_triangles = 1;
        }
        if (found_vertices && found_triangles) break;
    }

    fclose(fp);
    return EXIT_SUCCESS;
}
*/

int read_mesh2D(struct Mesh2D* m, const char* filename) {
    FILE* fp = fopen(filename, "r");
    if (!fp) return EXIT_FAILURE;

    char line[256];
    int nv = 0, nt = 0;

    while (fgets(line, sizeof(line), fp)) {
        if (strstr(line, "Vertices")) {
            fgets(line, sizeof(line), fp); // Read the number of vertices
            sscanf(line, "%d", &nv);
            if (initialize_mesh2D(m, nv, 0) != 0) {
            fclose(fp); 
            return EXIT_FAILURE; 
            }
            for (int i = 0; i < nv; i++) {
                fgets(line, sizeof(line), fp);
                sscanf(line, "%lf %lf %*f %*d", &m->vert[i].x, &m->vert[i].y);
            }
            m->nv = nv;
        }
        if (strstr(line, "Triangles")) {
            fgets(line, sizeof(line), fp); // Read the number of triangles
            sscanf(line, "%d", &nt);
            if (initialize_mesh2D(m, m->nv, nt) != 0) {
            fclose(fp); 
            return EXIT_FAILURE; 
            }
            for (int i = 0; i < nt; i++) {
                fgets(line, sizeof(line), fp);
                sscanf(line, "%d %d %d %*d",
                    &m->tri[i].Index[0],
                    &m->tri[i].Index[1],
                    &m->tri[i].Index[2]);
            }
            m->nt = nt;
        }
    }
    fclose(fp);
    return EXIT_SUCCESS;
}

int mesh2D_to_gnuplot(struct Mesh2D* m, const char* filename) {
    FILE* fp = fopen(filename, "w");
    if (!fp) return EXIT_FAILURE;

    for (int i = 0; i < m->nt; i++) {
        // Adjust for 1-based indexing in the .mesh file
        int v1 = m->tri[i].Index[0] - 1;
        int v2 = m->tri[i].Index[1] - 1;
        int v3 = m->tri[i].Index[2] - 1;

        fprintf(fp, "%lf %lf %lf\n", m->vert[v1].x, m->vert[v1].y);
        fprintf(fp, "%lf %lf %lf\n", m->vert[v2].x, m->vert[v2].y);
        fprintf(fp, "%lf %lf %lf\n", m->vert[v3].x, m->vert[v3].y);
        fprintf(fp, "%lf %lf %lf\n\n", m->vert[v1].x, m->vert[v1].y);
    }
    fclose(fp);
    return EXIT_SUCCESS;
}

int write_mesh2D(struct Mesh2D* m, const char* filename) {
    FILE* fp = fopen(filename, "w");
    if (!fp) return EXIT_FAILURE;

    fprintf(fp, "MeshVersionFormatted 1\n");
    fprintf(fp, "Dimension 2\n");
    fprintf(fp, "Vertices\n%d\n", m->nv);
    for (int i = 0; i < m->nv; i++) {
        fprintf(fp, "%lf %lf 0\n", m->vert[i].x, m->vert[i].y);
    }
    fprintf(fp, "Triangles\n%d\n", m->nt);
    for (int i = 0; i < m->nt; i++) {
        fprintf(fp, "%d %d %d 0\n",
            m->tri[i].Index[0],
            m->tri[i].Index[1],
            m->tri[i].Index[2]);
    }
    fprintf(fp, "End\n");

    fclose(fp);
    return EXIT_SUCCESS;
}