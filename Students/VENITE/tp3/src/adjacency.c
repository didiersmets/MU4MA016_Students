#include "../include/adjacency.h"
#include "../include/hash_table.h" // Pour la méthode 2
#include <stdlib.h>
#include <stdio.h>

// ----------------------------------------------------------------------------
// EXERCICE 1 & 2 : Fonctions utilitaires pour la Méthode 1
// ----------------------------------------------------------------------------

/**
 * @brief (Ex 1) Trouve la position de l'arête (v1, v2) dans un triangle t.
 * @return Position (0, 1, 2) ou -1 si non trouvée.
 */
static int edge_pos_in_tri(int v1, int v2, const Triangle* t) {
    if (t->v[0] == v1 && t->v[1] == v2) return 0;
    if (t->v[1] == v1 && t->v[2] == v2) return 1;
    if (t->v[2] == v1 && t->v[0] == v2) return 2;
    return -1;
}

/**
 * @brief (Ex 2) Détermine si deux triangles sont voisins.
 * @return Position de l'arête commune dans t1, ou -1 si non voisins.
 */
static int tris_are_neighbors(const Triangle* t1, const Triangle* t2) {
    for (int i = 0; i < 3; ++i) {
        int v1 = t1->v[i];
        int v2 = t1->v[(i + 1) % 3];
        // Cherche l'arête opposée (v2, v1) dans t2
        if (edge_pos_in_tri(v2, v1, t2) != -1) {
            return i; // Retourne la position de l'arête dans t1
        }
    }
    return -1;
}


// ----------------------------------------------------------------------------
// EXERCICE 3 : Méthode 1 - Naïve O(n^2)
// ----------------------------------------------------------------------------
int* build_adjacency_table1(const Mesh* m) {
    int n_tri = m->n_triangles;
    int* adj = (int*)malloc(3 * n_tri * sizeof(int));
    if (!adj) return NULL;

    // Initialisation à -1 (pas de voisin)
    for (int i = 0; i < 3 * n_tri; ++i) {
        adj[i] = -1;
    }

    for (int i = 0; i < n_tri; ++i) {
        for (int j = 0; j < n_tri; ++j) {
            if (i == j) continue;

            int pos = tris_are_neighbors(&m->triangles[i], &m->triangles[j]);
            if (pos != -1) {
                adj[3 * i + pos] = j;
            }
        }
    }
    return adj;
}


// ----------------------------------------------------------------------------
// EXERCICE 5 : Méthode 2 - Table de hachage générique
// ----------------------------------------------------------------------------
int* build_adjacency_table2(const Mesh* m) {
    int n_tri = m->n_triangles;
    int* adj = (int*)malloc(3 * n_tri * sizeof(int));
    if (!adj) return NULL;
    for (int i = 0; i < 3 * n_tri; ++i) adj[i] = -1;

    // Utilise une taille de table de hachage égale au nombre d'arêtes
    HashTable* ht = ht_create(3 * n_tri);
    if (!ht) { free(adj); return NULL; }

    // Remplir la table de hachage avec toutes les arêtes
    for (int i = 0; i < n_tri; ++i) {
        for (int j = 0; j < 3; ++j) {
            Edge e = {m->triangles[i].v[j], m->triangles[i].v[(j + 1) % 3]};
            ht_insert(ht, e, i);
        }
    }

    // Remplir la table d'adjacence
    for (int i = 0; i < n_tri; ++i) {
        for (int j = 0; j < 3; ++j) {
            // Arête opposée
            Edge opposite_edge = {m->triangles[i].v[(j + 1) % 3], m->triangles[i].v[j]};
            int neighbor_tri = ht_find(ht, opposite_edge);
            if (neighbor_tri != -1) {
                adj[3 * i + j] = neighbor_tri;
            }
        }
    }

    ht_dispose(ht);
    return adj;
}


// ----------------------------------------------------------------------------
// EXERCICE 6 : Méthode 3 - Table de hachage ad-hoc
// ----------------------------------------------------------------------------

typedef struct {
    int* head; // Taille: n_vertices
    int* next; // Taille: 3 * n_triangles
} EdgeTable;

// Initialise la table d'arêtes ad-hoc
static void edge_table_initialize(EdgeTable* et, int n_vert, int n_tri) {
    et->head = (int*)malloc(n_vert * sizeof(int));
    et->next = (int*)malloc(3 * n_tri * sizeof(int));
    for (int i = 0; i < n_vert; ++i) et->head[i] = -1;
    for (int i = 0; i < 3 * n_tri; ++i) et->next[i] = -1;
}

// Libère la mémoire
static void edge_table_dispose(EdgeTable* et) {
    if (et) {
        if (et->head) free(et->head);
        if (et->next) free(et->next);
    }
}

// Insère une arête dans la table ad-hoc
static void edge_table_insert(int v1, int edge_code, EdgeTable* et) {
    et->next[edge_code] = et->head[v1];
    et->head[v1] = edge_code;
}

// Trouve une arête dans la table ad-hoc
static int edge_table_find(int v1, int v2, const EdgeTable* et, const Mesh* m) {
    int edge_code = et->head[v1];
    while (edge_code != -1) {
        int tri_idx = edge_code / 3;
        int edge_idx = edge_code % 3;
        int v_end = m->triangles[tri_idx].v[(edge_idx + 1) % 3];
        if (v_end == v2) {
            return tri_idx;
        }
        edge_code = et->next[edge_code];
    }
    return -1;
}


int* build_adjacency_table3(const Mesh* m) {
    int n_vert = m->n_vertices;
    int n_tri = m->n_triangles;
    int* adj = (int*)malloc(3 * n_tri * sizeof(int));
    if (!adj) return NULL;
    for (int i = 0; i < 3 * n_tri; ++i) adj[i] = -1;

    EdgeTable et;
    edge_table_initialize(&et, n_vert, n_tri);

    // Remplir la table d'arêtes
    for (int i = 0; i < n_tri; ++i) {
        for (int j = 0; j < 3; ++j) {
            int v1 = m->triangles[i].v[j];
            int edge_code = 3 * i + j;
            edge_table_insert(v1, edge_code, &et);
        }
    }

    // Remplir la table d'adjacence
    for (int i = 0; i < n_tri; ++i) {
        for (int j = 0; j < 3; ++j) {
            int v1 = m->triangles[i].v[j];
            int v2 = m->triangles[i].v[(j + 1) % 3];
            // Cherche l'arête opposée (v2, v1)
            adj[3 * i + j] = edge_table_find(v2, v1, &et, m);
        }
    }
    
    edge_table_dispose(&et);
    return adj;
}
