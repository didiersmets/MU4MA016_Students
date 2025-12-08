// Hashtables and Mesh Adjacency 哈希表与网格邻接关系 (3)
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


 //朴素法构建邻接表：返回长度为 3*ntri 的数组 adj：对每个三角形 i 的第 j 条边，adj[3*i + j] = 邻接三角形索引；若该边为边界边（无邻居），则值为 -1
int *build_adjacency_table1(const Mesh *m) {
    int ntri = m->ntri;
    int *adj = (int *)malloc(sizeof(int) * 3 * ntri);
    if (!adj) return NULL;

    for (int i = 0; i < 3 * ntri; ++i) adj[i] = -1;

    // 两两三角形检查是否邻接
    for (int i = 0; i < ntri; ++i) {
        for (int j = i + 1; j < ntri; ++j) {
            int pos_i = tris_are_neighbors(i, j, m);
            if (pos_i != -1) {
                // i 的第 pos_i 条边邻接 j
                adj[3 * i + pos_i] = j;

                // 找出 j 中与 i 共享的边的位置
                int pos_j = tris_are_neighbors(j, i, m);
                if (pos_j != -1) {
                    adj[3 * j + pos_j] = i;
                }
            }
        }
    }
    return adj;
}

 // 复杂度 O(ntri^2)