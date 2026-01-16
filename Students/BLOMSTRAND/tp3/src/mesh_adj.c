#include "mesh_adjacency.h"
#include <stdlib.h>

// ex 1
int edge_pos_in_tri(int v1, int v2, struct Triangle t)
{

    int a = t.idx[0];
    int b = t.idx[1];
    int c = t.idx[2];

    if (v1 == a && v2 == b)
        return 0;
    if (v1 == b && v2 == c)
        return 1;
    if (v1 == c && v2 == a)
        return 2;

    return -1;
}

// ex2
int tris_are_neighbors(int tri1, int tri2, const struct Mesh *m)
{
    struct Triangle t1 = m->triangles[tri1];
    struct Triangle t2 = m->triangles[tri2];

    int v1[3] = {t1.idx[0], t1.idx[1], t1.idx[2]};
    int v2[3] = {t2.idx[0], t2.idx[1], t2.idx[2]};

    for (int j = 0; j < 3; j++)
    {
        int a = v1[j];
        int b = v1[(j + 1) % 3];

        for (int k = 0; k < 3; k++)
        {
            if (v2[k] == b && v2[(k + 1) % 3] == a)
                return j;
        }
    }

    return -1;
}

// ex 3
int *build_adjacency_table1(const struct Mesh *m)
{
    int ntri = m->ntri;

    int *adj = (int *)malloc((size_t)(3 * ntri) * sizeof(int));
    if (adj == NULL)
        return NULL;

    for (int i = 0; i < 3 * ntri; i++)
        adj[i] = -1;

    for (int i = 0; i < ntri; i++)
    {
        for (int k = 0; k < ntri; k++)
        {
            if (k == i)
                continue;

            int pos = tris_are_neighbors(i, k, m);
            if (pos != -1)
                adj[3 * i + pos] = k;
        }
    }

    return adj;
}

// ex 4
struct HashTable *build_edge_table1(const struct Mesh *m)
{
    int ntri = m->ntri;

    size_t cap = (size_t)(6 * ntri + 1);

    struct HashTable *ht = hash_table_init(cap, sizeof(struct Edge), sizeof(int));
    if (ht == NULL)
        return NULL;

    for (int i = 0; i < ntri; i++)
    {
        struct Triangle t = m->triangles[i];

        struct Edge e0 = {t.idx[0], t.idx[1]};
        struct Edge e1 = {t.idx[1], t.idx[2]};
        struct Edge e2 = {t.idx[2], t.idx[0]};

        hash_table_insert(ht, &e0, &i);
        hash_table_insert(ht, &e1, &i);
        hash_table_insert(ht, &e2, &i);
    }

    return ht;
}

// ex 5
int *build_adjacency_table2(const struct Mesh *m)
{
    int ntri = m->ntri;

    int *adj = (int *)malloc((size_t)(3 * ntri) * sizeof(int));
    if (adj == NULL)
        return NULL;

    for (int i = 0; i < 3 * ntri; i++)
        adj[i] = -1;

    struct HashTable *ht = build_edge_table1(m);
    if (ht == NULL)
    {
        free(adj);
        return NULL;
    }

    for (int i = 0; i < ntri; i++)
    {
        struct Triangle t = m->triangles[i];
        int v[3] = {t.idx[0], t.idx[1], t.idx[2]};

        for (int j = 0; j < 3; j++)
        {
            int a = v[j];
            int b = v[(j + 1) % 3];

            // leta efter motsatt oriented edge: b -> a
            struct Edge opp = {b, a};

            int *p = (int *)hash_table_find(ht, &opp);
            if (p != NULL && *p != i)
                adj[3 * i + j] = *p;
        }
    }

    hash_table_fini(ht);
    return adj;
}

// ex 6
void edge_table_initialize(struct EdgeTable *et, int nvert, int ntri)
{
    et->head = (int *)malloc((size_t)nvert * sizeof(int));
    et->next = (int *)malloc((size_t)(3 * ntri) * sizeof(int));

    for (int i = 0; i < nvert; i++)
        et->head[i] = -1;

    for (int i = 0; i < 3 * ntri; i++)
        et->next[i] = -1;
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
    int cur = et->head[v1];

    while (cur != -1)
    {
        int tri = cur / 3;
        int j = cur % 3;

        struct Triangle t = m->triangles[tri];
        int a = t.idx[j];
        int b = t.idx[(j + 1) % 3];

        if (a == v1 && b == v2)
            return cur;

        cur = et->next[cur];
    }

    return -1;
}

struct EdgeTable *build_edge_table3(const struct Mesh *m)
{
    struct EdgeTable *et = (struct EdgeTable *)malloc(sizeof(struct EdgeTable));
    if (et == NULL)
        return NULL;

    edge_table_initialize(et, m->nvert, m->ntri);

    for (int i = 0; i < m->ntri; i++)
    {
        struct Triangle t = m->triangles[i];
        for (int j = 0; j < 3; j++)
        {
            int v1 = t.idx[j];
            int edge_code = 3 * i + j;
            edge_table_insert(v1, edge_code, et);
        }
    }

    return et;
}

int *build_adjacency_table3(const struct Mesh *m)
{
    int ntri = m->ntri;

    int *adj = (int *)malloc((size_t)(3 * ntri) * sizeof(int));
    if (adj == NULL)
        return NULL;

    for (int i = 0; i < 3 * ntri; i++)
        adj[i] = -1;

    struct EdgeTable *et = build_edge_table3(m);
    if (et == NULL)
    {
        free(adj);
        return NULL;
    }

    for (int i = 0; i < ntri; i++)
    {
        struct Triangle t = m->triangles[i];
        int v[3] = {t.idx[0], t.idx[1], t.idx[2]};

        for (int j = 0; j < 3; j++)
        {
            int a = v[j];
            int b = v[(j + 1) % 3];

            int code = edge_table_find(b, a, et, m);
            if (code != -1)
                adj[3 * i + j] = code / 3;
        }
    }

    edge_table_dispose(et);
    free(et);
    return adj;
}
