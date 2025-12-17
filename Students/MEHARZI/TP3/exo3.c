#include <stdio.h>
#include <stdlib.h>

/* Structures de base */
struct Triangle {
    int v[3];
};

struct Mesh {
    int nvert;
    int ntri;
    struct Triangle *tri;
};

/* Fonctions exos précédents */
int edge_pos_in_tri(int v1, int v2, struct Triangle t) {
    for (int i = 0; i < 3; ++i)
        if (t.v[i] == v1 && t.v[(i + 1) % 3] == v2)
            return i;
    return -1;
}

int tris_are_neighbors(int tri1, int tri2, const struct Mesh *m) {
    const struct Triangle t1 = m->tri[tri1];
    const struct Triangle t2 = m->tri[tri2];
    for (int j = 0; j < 3; ++j) {
        int a = t1.v[j];
        int b = t1.v[(j + 1) % 3];
        if (edge_pos_in_tri(b, a, t2) != -1)
            return j;
    }
    return -1;
}

/* Début de l'exercice 3 */

int *build_adjacency_table1(const struct Mesh *m) {
    int n = m->ntri;
    int *adj = malloc(3 * n * sizeof(int));
    if (!adj) return NULL;  // vérifie allocation mémoire

    // Initialisation à -1 (c'est demandé dans l'énoncé)
    for (int i = 0; i < 3 * n; ++i)
        adj[i] = -1;

    for (int i = 0; i < n; ++i) {
        for (int k = 0; k < n; ++k) {
            if (i == k) continue;

            int pos = tris_are_neighbors(i, k, m);
            if (pos != -1)
                adj[3 * i + pos] = k;
        }
    }

    return adj;
}


int main(void) {
    struct Triangle T[] = {
        {1,2,3},
        {3,2,4},  // partage l’arête (2,3) avec tri 0
    };
    struct Mesh M = { .nvert = 5, .ntri = 2, .tri = T };

    int *adj = build_adjacency_table1(&M);

    for (int i = 0; i < 3*M.ntri; ++i)
        printf("adj[%d] = %d\n", i, adj[i]);

    free(adj);
    return 0;
}
