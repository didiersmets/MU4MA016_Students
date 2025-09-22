#pragma once

int initialize_mesh2D(struct Mesh2D* m, int vtx_capacity, int tri_capacity);
void dispose_mesh2D(struct Mesh2D* m);
double area_mesh2D(struct Mesh2D* m);

int initialize_mesh3D(struct Mesh3D* m, int vtx_capacity, int tri_capacity);
void dispose_mesh3D(struct Mesh3D* m);
double volume_mesh3D(struct Mesh3D* m);

int read_mesh2D(struct Mesh2D* m, const char* filename);
int write_mesh2D(struct Mesh2D* m, const char* filename);
int mesh2D_to_gnuplot(struct Mesh2D* m, const char* filename);


struct Vertex2D {
    double x, y;
};

struct Vertex3D {
    double x, y, z;
};

struct Triangle {
    int v1, v2, v3; // indices of the vertices
};

struct Mesh2D {
    struct Vertex2D* vertices;
    int num_vertices;
    struct Triangle* triangles;
    int num_triangles;
};

struct Mesh3D {
    struct Vertex3D* vertices;
    int num_vertices;
    struct Triangle* triangles;
    int num_triangles;
};