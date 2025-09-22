#ifndef _MESH_ADJACENCY_H
#define _MESH_ADJACENCY_H

#include "mesh.h"
#include "hash_tables.h"

struct Edge {
	int v1;
	int v2;
};

int edge_pos_in_tri(int v1, int v2, struct Triangle t) {
	if (v1 == t.v1 && v2 == t.v2) {
		return 0;
	} else if (v1 == t.v2 && v2 == t.v3) {
		return 1;
	} else if (v1 == t.v3 && v2 == t.v1) {
		return 2;
	}
	return -1;
}

int tris_are_neighbors(int tri1, int tri2, const struct Mesh *m) {
	struct Triangle t1 = m->triangles[tri1];
	struct Triangle t2 = m->triangles[tri2];
	
	int same = edge_pos_in_tri(t2.v2, t2.v1, t1);
	if(same != -1) {
		return same;
	}
	same = edge_pos_in_tri(t2.v3, t2.v2, t1);
	if(same != -1) {
		return same;
	}
	same = edge_pos_in_tri(t2.v1, t2.v3, t1);
	if(same != -1) {
		return same;
	}
}

int *build_adjacency_table1(const struct Mesh *m) {
	int* table = malloc(m->ntri * 3 * sizeof(int));
	for(int i=0; i < m->ntri * 3; i++) {
		table[i] = -1;
	}
	for(int i=0; i < m->ntri; i++) {
		for(int j=0; j < m->ntri; j++) {
			if(i != j) {
				int pos = tris_are_neighbors(i, j, m);
				if(pos != -1) {
					table[i * 3 + pos] = j;
				}
			}
		}
	}
}

struct Edge {
	int v1;
	int v2;
};

struct HashTable *build_edge_table1(const struct Mesh *m) {
	struct HashTable* ht = hash_table_init(m->ntri * 3 * 2, sizeof(struct Edge), sizeof(int));
	for(int i=0; i < m->ntri; i++) {
		struct Edge edge;
		edge.v1 = m->triangles[i].v1;
		edge.v2 = m->triangles[i].v2;
		hash_table_insert(ht, &edge, &i);
		edge.v1 = m->triangles[i].v2;
		edge.v2 = m->triangles[i].v3;
		hash_table_insert(ht, &edge, &i);
		edge.v1 = m->triangles[i].v3;
		edge.v2 = m->triangles[i].v1;
		hash_table_insert(ht, &edge, &i);
	}
}

int *build_adjacency_table2(const struct Mesh *m) {
	struct HashTable* ht = build_edge_table1(m);
	int* table = malloc(m->ntri * 3 * sizeof(int));
	for(int i=0; i < m->ntri; i++) {
		int* neighbor = hash_table_find(ht, &(struct Edge){m->triangles[i].v2, m->triangles[i].v1});
		if(neighbor) {
			table[i * 3 + 0] = *neighbor;
		} else {
			table[i * 3 + 0] = -1;
		}
		int* neighbor = hash_table_find(ht, &(struct Edge){m->triangles[i].v3, m->triangles[i].v2});
		if(neighbor) {
			table[i * 3 + 1] = *neighbor;
		} else {
			table[i * 3 + 1] = -1;
		}
		int* neighbor = hash_table_find(ht, &(struct Edge){m->triangles[i].v1, m->triangles[i].v3});
		if(neighbor) {
			table[i * 3 + 2] = *neighbor;
		} else {
			table[i * 3 + 2] = -1;
		}
	}
}

struct HashTable *build_edge_table2(const struct Mesh *m);

struct EdgeTable {
	int *head;
	int *next;
};

void edge_table_initialize(struct EdgeTable *et, int nvert, int ntri);

void edge_table_dispose(struct EdgeTable *et);

void edge_table_insert(int v1, int edge_code, struct EdgeTable *et);

int  edge_table_find(int v1, int v2, const struct EdgeTable *et, 
                                                const struct Mesh *m);

struct EdgeTable *build_edge_table3(const struct Mesh *m);

int *build_adjacency_table3(const struct Mesh *m);

#endif
