// indexed triangular meshes 索引化三角形 (1),(2),(3)
#include <stdio.h>
#include "vertex.h"
#ifndef VERTEX_H
#define VERTEX_H

typedef struct {
    double x;
    double y;
} Vertex;

typedef struct {
    int v[3];  // 顶点的索引（数组中第几个点）
} Triangle;

#include <stdio.h>

// for testing
int main(void) {
    Vertex vert[4] = {
        {0, 0},
        {1, 0},
        {0, 1},
        {1, 1}
    };

    Triangle t = {{0, 1, 2}};

    // 取出 t 对应的三个顶点
    Vertex a = vert[t.v[0]];
    Vertex b = vert[t.v[1]];
    Vertex c = vert[t.v[2]];

    printf("vertices for triangle is:\n");
    printf("A(%.1f, %.1f)\n", a.x, a.y);
    printf("B(%.1f, %.1f)\n", b.x, b.y);
    printf("C(%.1f, %.1f)\n", c.x, c.y);

    return 0;
}

typedef struct {
    int nv;  // 顶点数量
    Vertex* vert;  // 顶点数组
    int nt;  // 三角形数量
    Triangle* tri;  // 三角形数组
 }Mesh2D;
