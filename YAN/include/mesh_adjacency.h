#ifndef _MESH_ADJACENCY_H
#define _MESH_ADJACENCY_H

#include "mesh.h"
#include "hash_tables.h"



typedef struct Edge {
	int v1;
	int v2;
}Edge;

int edge_pos_in_tri(int v1, int v2, Triangle t);

int tris_are_neighbors(int tri1, int tri2, const Mesh *m);

int *build_adjacency_table1(const Mesh *m);

HashTable *build_edge_table1(const Mesh *m);

int *build_adjacency_table2(const Mesh *m);

HashTable *build_edge_table2(const Mesh *m);

typedef struct EdgeTable {
	int *head;
	int *next;
}EdgeTable;

void edge_table_initialize(EdgeTable *et, int nv, int nt);

void edge_table_dispose(EdgeTable *et);

void edge_table_insert(int v1, int edge_code, EdgeTable *et);

int  edge_table_find(int v1, int v2, const EdgeTable *et, 
                                                const Mesh *m);

EdgeTable *build_edge_table3(const Mesh *m);

int *build_adjacency_table3(const Mesh *m);

#endif
