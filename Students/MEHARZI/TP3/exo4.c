#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "mesh.h"           
#include "hash_tables.h"    
#include "mesh_adjacency.h"


/* FONCTION PRINCIPALE : construction de la table d'arêtes orientées */
/* Clé : struct Edge {int v1, v2} */
/* Valeur: int (index du triangle) */

struct HashTable *build_edge_table1(const struct Mesh *m)
{
    if (!m || m->ntri <= 0) return NULL;

    /* On insère 3*ntri arêtes orientées.
       Le HT grossit à 2/3 de sa capacité donc choisissons une capacité
       assez grande pour éviter le hash_table_grow (pas implémenté) */
    unsigned need = 3u * (unsigned)m->ntri;    // entrées à insérer
    unsigned capacity = need * 2;             // marge >= 1.5*need
    if (capacity < 8) capacity = 8;

    struct HashTable *ht =
        hash_table_init(capacity, sizeof(struct Edge), sizeof(int));
    if (!ht) return NULL;

    for (int i = 0; i < m->ntri; ++i) {
        const struct Triangle t = m->triangles[i];

        for (int j = 0; j < 3; ++j) {
            struct Edge e = { t.idx[j], t.idx[(j + 1) % 3] };
            int tri_index = i;
            hash_table_insert(ht, &e, &tri_index);   // copie clé+valeur
        }
    }
    return ht;
}
