// Hashtables and Mesh Adjacency 哈希表与网格邻接关系 (4) 使用哈希表构建边表
#include <stdio.h>
#include <stdlib.h>
#include "hash_tables.h"

typedef struct {
    int v[3];            // 三角形三个顶点的全局索引（按 a,b,c 顺序存放）
} Triangle;

typedef struct {
    int ntri;            // 三角形数量
    Triangle *tri;       // 三角形数组，长度 ntri
} Mesh;

typedef struct {
    int v1;  // 边的第一个顶点
    int v2;  // 边的第二个顶点
} Edge;

unsigned int hash_edge(Edge e) {
    // 确保 v1 < v2，这样 (v1,v2) 和 (v2,v1) 会得到相同的哈希值
    int min_v = (e.v1 < e.v2) ? e.v1 : e.v2;
    int max_v = (e.v1 < e.v2) ? e.v2 : e.v1;
    return (unsigned int)(min_v * 100003 + max_v);
}

// 比较两条边是否相等（无向边，所以 (v1,v2) == (v2,v1)）
int edge_equal(Edge e1, Edge e2) {
    return ((e1.v1 == e2.v1 && e1.v2 == e2.v2) || 
            (e1.v1 == e2.v2 && e1.v2 == e2.v1));
}

struct HashTable *build_edge_table1(const struct Mesh *m) {
    int estimated_edges = m->ntri * 2;
    struct HashTable *edge_table = hash_create(estimated_edges);
    
    if (!edge_table) {
        fprintf(stderr, "error：无法创建哈希表\n");
        return NULL;
    }
    for (int i = 0; i < m->ntri; i++) {
        Triangle t = m->tri[i];
        for (int j = 0; j < 3; j++) {
            Edge edge;
            edge.v1 = t.v[j];
            edge.v2 = t.v[(j + 1) % 3];
            // 这样 (a,b) 和 (b,a) 会被视为同一条边
            if (edge.v1 > edge.v2) {
                int temp = edge.v1;
                edge.v1 = edge.v2;
                edge.v2 = temp;
            }
            
            int *count_ptr = (int *)hash_get(edge_table, &edge);
            
            if (count_ptr != NULL) {
                // 边已存在，增加计数
                (*count_ptr)++;
            } else {
                // 边不存在，添加到哈希表
                int *new_count = (int *)malloc(sizeof(int));
                if (!new_count) {
                    fprintf(stderr, "error：内存分配失败\n");
                    hash_destroy(edge_table);
                    return NULL;
                }
                *new_count = 1;  // 初始计数为1
                
                // 为边的键分配内存
                Edge *edge_key = (Edge *)malloc(sizeof(Edge));
                if (!edge_key) {
                    fprintf(stderr, "error：内存分配失败\n");
                    free(new_count);
                    hash_destroy(edge_table);
                    return NULL;
                }
                edge_key->v1 = edge.v1;
                edge_key->v2 = edge.v2;
                
                // 插入哈希表
                hash_insert(edge_table, edge_key, new_count);
            }
        }
    }
    return edge_table;
}

int main() {
    Mesh test_mesh;
    test_mesh.ntri = 2;
    test_mesh.tri = (Triangle *)malloc(sizeof(Triangle) * 2);
    
    test_mesh.tri[0].v[0] = 0;
    test_mesh.tri[0].v[1] = 1;
    test_mesh.tri[0].v[2] = 2;
    
    test_mesh.tri[1].v[0] = 1;
    test_mesh.tri[1].v[1] = 3;
    test_mesh.tri[1].v[2] = 2;

    struct HashTable *edge_table = build_edge_table1(&test_mesh);
    
    if (edge_table) {
        printf("边表构建成功！\n");
        printf("提示：边 (1,2) 应该出现2次（被两个三角形共享）\n");
        printf("其他边应该各出现1次\n");

        hash_destroy(edge_table);
    }
    
    free(test_mesh.tri);
    return 0;
}