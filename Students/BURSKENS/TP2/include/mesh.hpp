#include <stddef.h>

struct Vertex {
    double x_coordinate;
    double y_coordinate;
};

struct Vector {
    double x_length;
    double y_length;
};

struct Triangle {
    int a;
    int b;
    int c;
};

struct Mesh2D {
    size_t nvert;
    size_t ntri;
    struct Vertex *vertices;
    struct Triangle *triangles;
};

int initialize_mesh2D(struct Mesh2D* m, int vtx_capacity, int tri_capacity);

void dispose_mesh2D(struct Mesh2D* m);

double area_mesh2D(struct Mesh2D* m);

//double vect(struct Vertex v_1, struct Vertex v_2);

int read_mesh2D(struct Mesh2D* m, const char* filename);

int write_mesh2D(struct Mesh2D* m, const char* filename);

int mesh2D_to_gnuplot(struct Mesh2D* m, const char* filename);
