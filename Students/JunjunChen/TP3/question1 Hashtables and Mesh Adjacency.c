// Hashtables and Mesh Adjacency 哈希表与网格邻接关系 (1)
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int v[3];            // 三角形三个顶点的全局索引（按 a,b,c 顺序存放）
} Triangle;

typedef struct {
    int ntri;            // 三角形数量
    Triangle *tri;       // 三角形数组，长度 ntri
} Mesh;

#define NEXT(i) (((i)+1)%3)
int edge_pos_in_tri(int v1, int v2, Triangle t) {
    // 三条有向边依次是 (v[0]->v[1]), (v[1]->v[2]), (v[2]->v[0])
    if (t.v[0] == v1 && t.v[1] == v2) return 0;
    if (t.v[1] == v1 && t.v[2] == v2) return 1;
    if (t.v[2] == v1 && t.v[0] == v2) return 2;
    return -1;
}