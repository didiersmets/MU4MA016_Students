// indexed triangular meshes 索引化三角形 (4)
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

typedef struct {
    int nv;  // 顶点数量
    Vertex* vert;  // 顶点数组
    int nt;  // 三角形数量
    Triangle* tri;  // 三角形数组
 }Mesh2D;

 
 int initialize_mesh2D(Mesh2D* m, int vtx_capacity, int tri_capacity) {
    m->nv = vtx_capacity;
    m->nt = tri_capacity;
    m->vert = (Vertex*) malloc(vtx_capacity * sizeof(Vertex));
    m->tri  = (Triangle*) malloc(tri_capacity * sizeof(Triangle));
    if (m->vert == NULL || m->tri == NULL) return -1;
    return 0;
}

