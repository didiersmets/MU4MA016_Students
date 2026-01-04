#ifndef TP3_ADJACENCY_H
#define TP3_ADJACENCY_H

#include <stdint.h>

/*
 * IMPORTANT:
 * This header assumes you have a mesh.h defining:
 *   struct Mesh { int nvert; int ntri; struct Triangle *tri; ... };
 *   struct Triangle { int v[3]; };
 *
 * If your field names differ, edit the macros below.
 */
#include "Mesh.h"

/* ---- adapter macros (edit these to match your mesh.h) ---- */
/* ---- adapter macros for YOUR mesh.h ---- */
#define MESH_NVERT(m) ((m)->nvert)
#define MESH_NTRI(m)  ((m)->ntri)
#define MESH_TRI(m,i) ((m)->triangles[(i)])

/* Your Triangle has either (v1,v2,v3) OR idx[3].
   Using idx[3] is the cleanest. */
#define TRI_V(t,k)    ((t).idx[(k)])


/* ---- exercise functions ---- */

/* Return 0/1/2 if (v1->v2) matches edge (0: v0->v1, 1: v1->v2, 2: v2->v0) in triangle t; else -1. */
int edge_pos_in_tri(int v1, int v2, struct Triangle t);

/* Return the edge position (0..2) in tri1 (index) such that tri2 shares the same edge with opposite orientation; else -1. */
int tris_are_neighbors(const struct Mesh *m, int tri1, int tri2);

/* Build adjacency table with O(ntri^2) search. Returns int* of length 3*ntri. Caller frees. */
int *build_adjacency_table1(const struct Mesh *m);

/* Build adjacency using hash table keyed by directed edges. Returns int* length 3*ntri. Caller frees. */
int *build_adjacency_table2(const struct Mesh *m);

/* Build adjacency using ad-hoc edge table (head/next lists by first vertex). Returns int* length 3*ntri. Caller frees. */
int *build_adjacency_table3(const struct Mesh *m);

#endif
