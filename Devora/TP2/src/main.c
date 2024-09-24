#include <stdio.h>

struct Vertex {
    float x;
    float y;
} ;

struct Triangle{
    struct Vertex vertices[3];
};

struct Mesh2D {
    
};

int main() {
    struct Vertex p1 = {0.0, 0.0};
    struct Vertex p2 = {1.0, 0.0};
    struct Vertex p3 = {0.0, 1.0};

    struct Triangle T;
    T.vertices[0] = p1;
    T.vertices[1] = p2;
    T.vertices[2] = p3;

    for (int i = 0; i < 3; i++) {
        printf("x: %f / y: %f\n", T.vertices[i].x, T.vertices[i].y);
    }
    return 0;
}