// Hashtables and Mesh Adjacency 哈希表与网格邻接关系 (5)
#include <stdio.h>
#include <stdlib.h>
#include "hash_tables.h"

typedef struct {
    int v[3];
} Triangle;

typedef struct {
    int ntri;
    Triangle *tri;
} Mesh;

typedef struct {
    int v1, v2;  // 有向边
} Edge;

typedef struct {
    int triangle_id;  // 属于哪个三角形
    int edge_id;      // 是第几条边
} EdgeInfo;

int *build_adjacency_table2(const Mesh *m) {
    int ntri = m->ntri;
    HashTable *edge_table = hash_create(ntri * 3);
    if (!edge_table) return NULL;
    for (int i = 0; i < ntri; i++) {
        for (int j = 0; j < 3; j++) {
            // 创建边 (v1 -> v2)
            Edge *key = malloc(sizeof(Edge));
            key->v1 = m->tri[i].v[j];
            key->v2 = m->tri[i].v[(j + 1) % 3];
            EdgeInfo *info = malloc(sizeof(EdgeInfo));
            info->triangle_id = i;
            info->edge_id = j;
            hash_insert(edge_table, key, info);
        }
    }
    
    //初始化为 -1
    int *adj = malloc(sizeof(int) * 3 * ntri);
    for (int i = 0; i < 3 * ntri; i++) {
        adj[i] = -1;
    }
    for (int i = 0; i < ntri; i++) {
        for (int j = 0; j < 3; j++) {
            int v1 = m->tri[i].v[j];
            int v2 = m->tri[i].v[(j + 1) % 3];
            
            Edge reverse = {v2, v1};
            EdgeInfo *neighbor = hash_get(edge_table, &reverse);
            if (neighbor) {
                adj[3 * i + j] = neighbor->triangle_id;
                adj[3 * neighbor->triangle_id + neighbor->edge_id] = i;
            }
        }
    }
    hash_destroy(edge_table);
    return adj;
}