// Hashtables and Mesh Adjacency 哈希表与网格邻接关系 (2)
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

 //判断两个三角形是否共享一条公共边（方向相反）；若相邻则返回该公共边在 tri1 中的位置（0/1/2），否则返回 -1
int tris_are_neighbors(int tri1, int tri2, const Mesh *m) {
    const Triangle t1 = m->tri[tri1];
    const Triangle t2 = m->tri[tri2];

    // 枚举 tri1 的三条边 (a->b)
    for (int i = 0; i < 3; ++i) {
        int a = t1.v[i];
        int b = t1.v[NEXT(i)];
        // tri2 若与之相邻，必须包含反向边 (b->a)
        int pos_in_t2 = edge_pos_in_tri(b, a, t2);
        if (pos_in_t2 != -1) {
            // 返回该公共边在 tri1 中的位置 i
            return i;
        }
    }
    return -1;
}