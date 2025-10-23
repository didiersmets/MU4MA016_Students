#ifndef MESH_UTILS_H
#define MESH_UTILS_H

typedef struct {
    double x, y, z;
} Vertex;


typedef struct {
    int v[3];
} Triangle;

typedef struct {
    int n_vertices;
    Vertex* vertices;
    int n_triangles;
    Triangle* triangles;
} Mesh;


Mesh* mesh_read(const char* filename);

void mesh_dispose(Mesh* m);

#endif // MESH_UTILS_H
