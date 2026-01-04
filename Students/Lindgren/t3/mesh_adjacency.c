

#include <stdlib.h>
#include "mesh_adjacency.h"


int edge_pos_in_tri(int v1, int v2, struct Triangle t)
{
    if (t.idx[0] == v1 && t.idx[1] == v2) return 0;
    if (t.idx[1] == v1 && t.idx[2] == v2) return 1;
    if (t.idx[2] == v1 && t.idx[0] == v2) return 2;
    return -1;
}


int tris_are_neighbors(int tri1, int tri2, const struct Mesh *m)
{
    struct Triangle t1 = m->triangles[tri1];
    struct Triangle t2 = m->triangles[tri2];

    if (edge_pos_in_tri(t1.idx[1], t1.idx[0], t2) != -1) return 0;
    if (edge_pos_in_tri(t1.idx[2], t1.idx[1], t2) != -1) return 1;
    if (edge_pos_in_tri(t1.idx[0], t1.idx[2], t2) != -1) return 2;

    return -1;
}


int *build_adjacency_table1(const struct Mesh *m)
{
    if (!m || !m->triangles || m->ntri <= 0) return NULL;

    int *adj = (int*)malloc((size_t)3 * (size_t)m->ntri * sizeof(int));
    if (!adj) return NULL;

    for (int i = 0; i < 3 * m->ntri; ++i) adj[i] = -1;

    for (int i = 0; i < m->ntri; ++i) {
        for (int k = 0; k < m->ntri; ++k) {
            if (i == k) continue;
            int pos = tris_are_neighbors(i, k, m);
            if (pos != -1) {
                adj[3*i + pos] = k;
            }
        }
    }
    return adj;
}


struct HashTable *build_edge_table1(const struct Mesh *m)
{
    if (!m || !m->triangles) return NULL;

    size_t capacity = (size_t)6 * (size_t)m->ntri;
    struct HashTable *ht = hash_table_init(capacity, sizeof(struct Edge), sizeof(int));
    if (!ht) return NULL;

    for (int tri = 0; tri < m->ntri; ++tri) {
        struct Triangle t = m->triangles[tri];

        for (int e = 0; e < 3; ++e) {
            struct Edge key;
            key.v1 = t.idx[e];
            key.v2 = t.idx[(e + 1) % 3];

            int tri_index = tri;
            hash_table_insert(ht, &key, &tri_index);
        }
    }
    return ht;
}


struct HashTable *build_edge_table2(const struct Mesh *m)
{
    if (!m || !m->triangles) return NULL;

    size_t capacity = (size_t)4 * (size_t)m->ntri;
    struct HashTable *ht = hash_table_init(capacity, sizeof(struct Edge), sizeof(int));
    if (!ht) return NULL;

    for (int tri = 0; tri < m->ntri; ++tri) {
        struct Triangle t = m->triangles[tri];

        for (int e = 0; e < 3; ++e) {
            struct Edge key;
            key.v1 = t.idx[e];
            key.v2 = t.idx[(e + 1) % 3];

            int tri_index = tri;
            hash_table_insert(ht, &key, &tri_index);
        }
    }
    return ht;
}

int *build_adjacency_table2(const struct Mesh *m)
{
    if (!m || !m->triangles) return NULL;

    struct HashTable *ht = build_edge_table1(m);
    if (!ht) return NULL;

    int *adj = (int*)malloc((size_t)3 * (size_t)m->ntri * sizeof(int));
    if (!adj) {
        hash_table_fini(ht);
        free(ht);
        return NULL;
    }

    for (int i = 0; i < 3 * m->ntri; ++i) adj[i] = -1;

    for (int tri = 0; tri < m->ntri; ++tri) {
        struct Triangle t = m->triangles[tri];

        for (int e = 0; e < 3; ++e) {
            /* reversed key: (v2 -> v1) */
            struct Edge key;
            key.v1 = t.idx[(e + 1) % 3];
            key.v2 = t.idx[e];

            int *found_tri = (int*)hash_table_find(ht, &key);
            if (found_tri) {
                adj[3*tri + e] = *found_tri;
            }
        }
    }

    hash_table_fini(ht);
    free(ht);
    return adj;
}



void edge_table_initialize(struct EdgeTable *et, int nvert, int ntri)
{
    et->head = (int*)malloc((size_t)nvert * sizeof(int));
    et->next = (int*)malloc((size_t)3 * (size_t)ntri * sizeof(int));

    for (int i = 0; i < nvert; ++i) et->head[i] = -1;
    for (int i = 0; i < 3 * ntri; ++i) et->next[i] = -1;
}

void edge_table_dispose(struct EdgeTable *et)
{
    free(et->head);
    free(et->next);
    et->head = NULL;
    et->next = NULL;
}

void edge_table_insert(int v1, int edge_code, struct EdgeTable *et)
{
    int tmp = et->head[v1];
    et->head[v1] = edge_code;
    et->next[edge_code] = tmp;
}

int edge_table_find(int v1, int v2,
                    const struct EdgeTable *et,
                    const struct Mesh *m)
{
    int code = et->head[v1];

    while (code != -1) {
        int tri  = code / 3;
        int edge = code % 3;

        int a = m->triangles[tri].idx[edge];
        int b = m->triangles[tri].idx[(edge + 1) % 3];

        if (a == v1 && b == v2) return code;
        code = et->next[code];
    }
    return -1;
}

struct EdgeTable *build_edge_table3(const struct Mesh *m)
{
    if (!m || !m->triangles) return NULL;

    struct EdgeTable *et = (struct EdgeTable*)malloc(sizeof(struct EdgeTable));
    if (!et) return NULL;

    edge_table_initialize(et, m->nvert, m->ntri);

    for (int tri = 0; tri < m->ntri; ++tri) {
        struct Triangle t = m->triangles[tri];
        for (int e = 0; e < 3; ++e) {
            int edge_code = 3*tri + e;
            edge_table_insert(t.idx[e], edge_code, et);
        }
    }
    return et;
}

int *build_adjacency_table3(const struct Mesh *m)
{
    if (!m || !m->triangles) return NULL;

    struct EdgeTable *et = build_edge_table3(m);
    if (!et) return NULL;

    int *adj = (int*)malloc((size_t)3 * (size_t)m->ntri * sizeof(int));
    if (!adj) {
        edge_table_dispose(et);
        free(et);
        return NULL;
    }

    for (int i = 0; i < 3 * m->ntri; ++i) adj[i] = -1;

    for (int tri = 0; tri < m->ntri; ++tri) {
        struct Triangle t = m->triangles[tri];

        for (int e = 0; e < 3; ++e) {
            int code = edge_table_find(
                t.idx[(e + 1) % 3],
                t.idx[e],
                et,
                m
            );
            if (code != -1) {
                adj[3*tri + e] = code / 3;
            }
        }
    }

    edge_table_dispose(et);
    free(et);
    return adj;
}
