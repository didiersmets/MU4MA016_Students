#include "Mesh2D.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int initialize_mesh2D(struct Mesh2D* m, int vert_capacity, int tri_capacity) {
    m->nv = 0;
    m->nt = 0;

    m->vertices = (struct Vertex*) malloc(sizeof(struct Vertex) * vert_capacity);
    m->triangles = (struct Triangle*) malloc(sizeof(struct Triangle) * tri_capacity);

    return 0;
}

int dispose_mesh2D(struct Mesh2D* m) {
    free(m->vertices);
    m->vertices = NULL;
    
    free(m->triangles);
    m->triangles = NULL;

    return 0;
}

double area_mesh2D(struct Mesh2D* m) {
    double area = 0.0;

    for (int i = 0; i < m->nt; i++) {
        struct Triangle* tri = &m->triangles[i];
        struct Vertex* v1 = &m->vertices[tri->v1];
        struct Vertex* v2 = &m->vertices[tri->v2];
        struct Vertex* v3 = &m->vertices[tri->v3];

        // Calculate signed area of triangle
        area += 0.5 * (v1->x * (v2->y - v3->y) + v2->x * (v3->y - v1->y) + v3->x * (v1->y - v2->y));
    }

    return area;
}

int read_mesh2D(struct Mesh2D* m, const char* filename) {
    char keyword[256];
    char line[256];
    int version, dimension;

    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error: Could not open file %s\n", filename);
        return 1;
    }

    // Read version
    fscanf(file, "%s %d", keyword, &version);
    if (strcmp(keyword, "MeshVersionFormatted") != 0 || version != 2) {
        printf("Error: Invalid mesh version\n");
        fclose(file);
        return 1;
    }

    // Read dimension
    fscanf(file, "%s %d", keyword, &dimension);
    if (strcmp(keyword, "Dimension") != 0 || dimension != 2)
        printf("Warning: Mesh ist not 2-dimensional\n");

    // Read number of vertices
    fscanf(file, "%s %d", keyword, &m->nv);
    if (strcmp(keyword, "Vertices") != 0) {
        printf("Error: Expected Vertices\n");
        fclose(file);
        return 1;
    }
    // allocate space for them
    m->vertices = (struct Vertex*) malloc(sizeof(struct Vertex) * m->nv);

    // Read all vertices
    for (int i = 0; i < m->nv; i++) {
        fscanf(file, "%lf %lf", &m->vertices[i].x, &m->vertices[i].y);
        fgets(line, sizeof(line), file);  // discard rest of the line
    }

    // Read number of triangles
    fscanf(file, "%s %d", keyword, &m->nt);
    if (strcmp(keyword, "Triangles") != 0) {
        printf("Error: Expected Triangles\n");
        fclose(file);
        free(m->vertices);
        return 1;
    }
    // allocate space for them
    m->triangles = (struct Triangle*) malloc(sizeof(struct Triangle) * m->nt);

    // Read all triangles
    for (int i = 0; i < m->nt; i++) {
        fscanf(file, "%d %d %d", &m->triangles[i].v1, &m->triangles[i].v2, &m->triangles[i].v3);
        fgets(line, sizeof(line), file); // discard rest of the line
    }

    return 0;
}

int mesh2D_to_gnuplot(struct Mesh2D* m, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("Error: Could not open %s for writing.\n", filename);
        return 1;
    }

    for (int i = 0; i < m->nt; i++) {
        struct Triangle* t = &m->triangles[i];
        struct Vertex* v1 = &m->vertices[t->v1];
        struct Vertex* v2 = &m->vertices[t->v2];
        struct Vertex* v3 = &m->vertices[t->v3];

        // Edge v1 -> v2
        fprintf(file, "%lf %lf\n", v1->x, v1->y);
        fprintf(file, "%lf %lf\n\n", v2->x, v2->y);

        // Edge v2 -> v3
        fprintf(file, "%lf %lf\n", v2->x, v2->y);
        fprintf(file, "%lf %lf\n\n", v3->x, v3->y);

        // Edge v3 -> v1
        fprintf(file, "%lf %lf\n", v3->x, v3->y);
        fprintf(file, "%lf %lf\n\n", v1->x, v1->y);
    }

    fclose(file);
    return 0;
}


int write_mesh2D(struct Mesh2D* m, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("Error: Could not open %s for writing.\n", filename);
        return 1;
    }

    fprintf(file, "MeshVersionFormatted 2\n");
    fprintf(file, "Dimension 2\n\n");

    // Write vertices
    fprintf(file, "Vertices\n%d\n", m->nv);
    for (int i = 0; i < m->nv; i++) {
        fprintf(file, "%lf %lf 0\n", m->vertices[i].x, m->vertices[i].y);
    }

    fprintf(file, "\n");

    // Write triangles
    fprintf(file, "Triangles\n%d\n", m->nt);
    for (int i = 0; i < m->nt; i++) {
        fprintf(file, "%d %d %d 0\n",
                m->triangles[i].v1,
                m->triangles[i].v2,
                m->triangles[i].v3);
    }

    fclose(file);
    return 0;
}
