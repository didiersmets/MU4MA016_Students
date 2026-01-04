#include "Tp3_Actual.h"
#include "Hash_tables.h"

#include <stdlib.h>
#include <string.h>

/* Pack a directed edge (v1, v2) into one uint64_t key. */
static uint64_t pack_edge(int v1, int v2) {
    /* Cast to unsigned to avoid sign-extension issues. */
    uint32_t a = (uint32_t)v1;
    uint32_t b = (uint32_t)v2;
    return ((uint64_t)a << 32) | (uint64_t)b;
}

/* ---------------- Exercise 1 ---------------- */

int edge_pos_in_tri(int v1, int v2, struct Triangle t) {
    int a = TRI_V(t, 0);
    int b = TRI_V(t, 1);
    int c = TRI_V(t, 2);

    /* Directed edges are: (a->b), (b->c), (c->a). */
    if (a == v1 && b == v2) return 0;
    if (b == v1 && c == v2) return 1;
    if (c == v1 && a == v2) return 2;
    return -1;
}

/* ---------------- Exercise 2 ---------------- */

int tris_are_neighbors(const struct Mesh *m, int tri1, int tri2) {
    struct Triangle t1 = MESH_TRI(m, tri1);
    struct Triangle t2 = MESH_TRI(m, tri2);

    /* For each directed edge in t1, check whether t2 contains the reverse directed edge. */
    for (int e = 0; e < 3; e++) {
        int v1 = TRI_V(t1, e);
        int v2 = TRI_V(t1, (e + 1) % 3);

        /* Neighbor must have (v2 -> v1) as one of its directed edges. */
        if (edge_pos_in_tri(v2, v1, t2) != -1) {
            return e; /* position in tri1 */
        }
    }
    return -1;
}

/* ---------------- Exercise 3 (O(n^2)) ---------------- */

int *build_adjacency_table1(const struct Mesh *m) {
    int ntri = MESH_NTRI(m);

    int *adj = (int *)malloc((size_t)(3 * ntri) * sizeof(int));
    if (!adj) return NULL;

    for (int i = 0; i < 3 * ntri; i++) adj[i] = -1;

    for (int i = 0; i < ntri; i++) {
        for (int j = i + 1; j < ntri; j++) {
            int pos_i = tris_are_neighbors(m, i, j);
            if (pos_i != -1) {
                adj[3 * i + pos_i] = j;

                int pos_j = tris_are_neighbors(m, j, i);
                if (pos_j != -1) {
                    adj[3 * j + pos_j] = i;
                }
            }
        }
    }

    return adj;
}

/* ---------------- Exercise 4/5 (hash directed edges) ---------------- */

/*
 * Build a hash table mapping each directed edge (v1,v2) to the triangle index owning it.
 * If your mesh may be non-manifold, you might need to store lists; TP typically assumes well-formed triangulations.
 */
static HashTable *build_edge_table_hash(const struct Mesh *m) {
    int ntri = MESH_NTRI(m);
    size_t nedges = (size_t)(3 * ntri);

    /* Capacity ~ 2x edges to keep load factor low. */
    HashTable *ht = hash_table_init(nedges * 2);
    if (!ht) return NULL;

    for (int i = 0; i < ntri; i++) {
        struct Triangle t = MESH_TRI(m, i);
        for (int e = 0; e < 3; e++) {
            int v1 = TRI_V(t, e);
            int v2 = TRI_V(t, (e + 1) % 3);

            uint64_t key = pack_edge(v1, v2);
            /* If duplicates occur, later ones overwrite; acceptable for manifold assumptions. */
            if (hash_table_put(ht, key, i) < 0) {
                hash_table_fini(ht);
                return NULL;
            }
        }
    }

    return ht;
}

int *build_adjacency_table2(const struct Mesh *m) {
    int ntri = MESH_NTRI(m);

    int *adj = (int *)malloc((size_t)(3 * ntri) * sizeof(int));
    if (!adj) return NULL;
    for (int i = 0; i < 3 * ntri; i++) adj[i] = -1;

    HashTable *ht = build_edge_table_hash(m);
    if (!ht) {
        free(adj);
        return NULL;
    }

    for (int i = 0; i < ntri; i++) {
        struct Triangle t = MESH_TRI(m, i);

        for (int e = 0; e < 3; e++) {
            int v1 = TRI_V(t, e);
            int v2 = TRI_V(t, (e + 1) % 3);

            /* Opposing edge must be (v2, v1). */
            uint64_t opp = pack_edge(v2, v1);

            int nei = -1;
            if (hash_table_get(ht, opp, &nei)) {
                adj[3 * i + e] = nei;
            } else {
                adj[3 * i + e] = -1; /* boundary edge */
            }
        }
    }

    hash_table_fini(ht);
    return adj;
}

/* ---------------- Exercise 6 (ad-hoc edge table: head/next by first vertex) ---------------- */

typedef struct {
    int nvert;
    int nedge;   /* equals 3*ntri */

    int *head;   /* size nvert, head[v] = first edge-code in chain or -1 */
    int *next;   /* size nedge, next[code] = next code in chain or -1 */
    int *v2;     /* size nedge, v2[code] = second vertex of directed edge */
} EdgeTable;

/* edge-code is: code = 3*tri + e */
static EdgeTable *edge_table_init(const struct Mesh *m) {
    int nvert = MESH_NVERT(m);
    int ntri  = MESH_NTRI(m);
    int nedge = 3 * ntri;

    EdgeTable *et = (EdgeTable *)calloc(1, sizeof(EdgeTable));
    if (!et) return NULL;

    et->nvert = nvert;
    et->nedge = nedge;

    et->head = (int *)malloc((size_t)nvert * sizeof(int));
    et->next = (int *)malloc((size_t)nedge * sizeof(int));
    et->v2   = (int *)malloc((size_t)nedge * sizeof(int));

    if (!et->head || !et->next || !et->v2) {
        free(et->head);
        free(et->next);
        free(et->v2);
        free(et);
        return NULL;
    }

    for (int i = 0; i < nvert; i++) et->head[i] = -1;
    for (int i = 0; i < nedge; i++) et->next[i] = -1;

    /* Build chains keyed by first vertex v1. */
    for (int tri = 0; tri < ntri; tri++) {
        struct Triangle t = MESH_TRI(m, tri);

        for (int e = 0; e < 3; e++) {
            int v1 = TRI_V(t, e);
            int vv2 = TRI_V(t, (e + 1) % 3);

            int code = 3 * tri + e;

            et->v2[code] = vv2;
            et->next[code] = et->head[v1];
            et->head[v1] = code;
        }
    }

    return et;
}

static void edge_table_free(EdgeTable *et) {
    if (!et) return;
    free(et->head);
    free(et->next);
    free(et->v2);
    free(et);
}

/* Find triangle that owns directed edge (v1->v2). Return triangle index or -1 if not found. */
static int edge_table_find_tri(const EdgeTable *et, int v1, int v2) {
    if (v1 < 0 || v1 >= et->nvert) return -1;

    for (int code = et->head[v1]; code != -1; code = et->next[code]) {
        if (et->v2[code] == v2) {
            return code / 3;
        }
    }
    return -1;
}

int *build_adjacency_table3(const struct Mesh *m) {
    int ntri = MESH_NTRI(m);

    int *adj = (int *)malloc((size_t)(3 * ntri) * sizeof(int));
    if (!adj) return NULL;
    for (int i = 0; i < 3 * ntri; i++) adj[i] = -1;

    EdgeTable *et = edge_table_init(m);
    if (!et) {
        free(adj);
        return NULL;
    }

    for (int tri = 0; tri < ntri; tri++) {
        struct Triangle t = MESH_TRI(m, tri);

        for (int e = 0; e < 3; e++) {
            int v1 = TRI_V(t, e);
            int v2 = TRI_V(t, (e + 1) % 3);

            /* neighbor is owner of (v2 -> v1) */
            int nei = edge_table_find_tri(et, v2, v1);
            adj[3 * tri + e] = nei;
        }
    }

    edge_table_free(et);
    return adj;
}
