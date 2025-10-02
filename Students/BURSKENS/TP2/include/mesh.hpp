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

int initialize mesh2D(struct Mesh2D* m, int vtx capacity, int tri capacity);

void dispose mesh2D(struct Mesh2D* m);

double area mesh2D(struct Mesh2D* m);

double vect(struct Vertex v_1, struct Vertex v_2);

int read mesh2D(struct Mesh2D* m, const char* filename);
