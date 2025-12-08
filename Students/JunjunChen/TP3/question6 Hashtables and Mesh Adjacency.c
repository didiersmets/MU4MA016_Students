// Hashtables and Mesh Adjacency 哈希表与网格邻接关系 (6)
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int v[3];
} Triangle;

typedef struct {
    int ntri;
    Triangle *tri;
} Mesh;

typedef struct {
    int *head;  // head[nvert]: 每个顶点的链表头
    int *next;  // next[3*ntri]: 边的链接
} EdgeTable;

void edge_table_initialize(struct EdgeTable *et, int nvert, int ntri) {
    et->head = (int *)malloc(sizeof(int) * nvert);
    et->next = (int *)malloc(sizeof(int) * 3 * ntri);
    for (int i = 0; i < nvert; i++) {
        et->head[i] = -1;
    }
    
    for (int i = 0; i < 3 * ntri; i++) {
        et->next[i] = -1;
    }
}

void edge_table_dispose(struct EdgeTable *et) {
    free(et->head);
    free(et->next);
}

void edge_table_insert(int v1, int edge_code, struct EdgeTable *et) {
    int tmp = et->head[v1];
    et->head[v1] = edge_code;
    et->next[edge_code] = tmp;
}

int edge_table_find(int v1, int v2, const struct EdgeTable *et,
                    const struct Mesh *m) {
    int current = et->head[v1];
    while (current != -1) {
        int tri_idx = current / 3;
        int edge_idx = current % 3;
        int start = m->tri[tri_idx].v[edge_idx];
        int end = m->tri[tri_idx].v[(edge_idx + 1) % 3];
        if (start == v1 && end == v2) {
            return current;
        }
        current = et->next[current];
    }
    
    return -1;
}

struct EdgeTable *build_edge_table3(const struct Mesh *m) {
    int ntri = m->ntri;
    int max_v = -1;
    for (int i = 0; i < ntri; i++) {
        for (int j = 0; j < 3; j++) {
            if (m->tri[i].v[j] > max_v) {
                max_v = m->tri[i].v[j];
            }
        }
    }
    int nvert = max_v + 1;
    struct EdgeTable *et = malloc(sizeof(struct EdgeTable));
    if (!et) return NULL;
    
    edge_table_initialize(et, nvert, ntri);
    for (int i = 0; i < ntri; i++) {
        for (int j = 0; j < 3; j++) {
            int v1 = m->tri[i].v[j];
            int edge_code = 3 * i + j;
            
            edge_table_insert(v1, edge_code, et);
        }
    }
    
    return et;
}

int *build_adjacency_table3(const struct Mesh *m) {
    int ntri = m->ntri;
    struct EdgeTable *et = build_edge_table3(m);
    if (!et) return NULL;
    int *adj = malloc(sizeof(int) * 3 * ntri);
    if (!adj) {
        edge_table_dispose(et);
        free(et);
        return NULL;
    }
    // 初始化为 -1
    for (int i = 0; i < 3 * ntri; i++) {
        adj[i] = -1;
    }
    for (int i = 0; i < ntri; i++) {
        for (int j = 0; j < 3; j++) {
            // v1 -> v2
            int v1 = m->tri[i].v[j];
            int v2 = m->tri[i].v[(j + 1) % 3];
            
            // v2 -> v1
            int reverse = edge_table_find(v2, v1, et, m);
            
            if (reverse != -1) {
                int nbr_tri = reverse / 3;
                int nbr_edge = reverse % 3;
                
                adj[3 * i + j] = nbr_tri;
                adj[3 * nbr_tri + nbr_edge] = i;
            }
        }
    }
    edge_table_dispose(et);
    free(et);
    
    return adj;
}