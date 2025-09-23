#ifndef _MESH_ADJACENCY_H
#define _MESH_ADJACENCY_H

#include "mesh.h"
#include "hash_tables.h"
#include <stdlib.h>

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

#include <stdio.h>

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
		if (i % 1000 == 0) {
			printf("Processed %d / %d triangles\n", i, m->ntri);
		}
	}
	return table;
}


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
	return ht;
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
		neighbor = hash_table_find(ht, &(struct Edge){m->triangles[i].v3, m->triangles[i].v2});
		if(neighbor) {
			table[i * 3 + 1] = *neighbor;
		} else {
			table[i * 3 + 1] = -1;
		}
		neighbor = hash_table_find(ht, &(struct Edge){m->triangles[i].v1, m->triangles[i].v3});
		if(neighbor) {
			table[i * 3 + 2] = *neighbor;
		} else {
			table[i * 3 + 2] = -1;
		}
	}

	hash_table_fini(ht);
	return table;
}

struct EdgeTable {
	int *head;
	int *next;
};

void edge_table_init(struct EdgeTable *et, int nvert, int ntri) {
	et->head = malloc(nvert * sizeof(int));
	et->next = malloc(ntri * 3 * sizeof(int));
	for(int i=0; i < nvert; i++) {
		et->head[i] = -1;
	}
}

void edge_table_dispose(struct EdgeTable *et) {
	free(et->head);
	free(et->next);
	free(et);
}

void edge_table_insert(struct EdgeTable *et, int v1, int edge_code) {
	int temp = et->head[v1];
	et->head[v1] = edge_code;
	et->next[edge_code] = temp;
}

int edge_table_find(const struct EdgeTable *et, int v1, int v2, 
                                                const struct Mesh *m) {
	int current = et->head[v1];
	while(current != -1) {
		int tri_idx = current / 3;
		int match = 0;
		switch (current % 3)
		{
		case 0:
			match = (m->triangles[tri_idx].v2 == v2);
			break;

		case 1:
			match = (m->triangles[tri_idx].v3 == v2);
			break;

		case 2:
			match = (m->triangles[tri_idx].v1 == v2);
			break;
		}
		if(match) {
			return tri_idx;
		}
		current = et->next[current];
	}
	return -1;
}

struct EdgeTable *build_edge_table3(const struct Mesh *m) {
	struct EdgeTable *et = malloc(sizeof(struct EdgeTable));
	edge_table_init(et, m->nvert, m->ntri);
	for(int i=0; i < m->ntri; i++) {
		edge_table_insert(et, m->triangles[i].v1, 3*i + 0);
		edge_table_insert(et, m->triangles[i].v2, 3*i + 1);
		edge_table_insert(et, m->triangles[i].v3, 3*i + 2);
	}
	return et;
}

int *build_adjacency_table3(const struct Mesh *m) {
	struct EdgeTable *et = build_edge_table3(m);
	int* table = malloc(m->ntri * 3 * sizeof(int));
	for(int i=0; i < m->ntri; i++) {
		int neighbor = edge_table_find(et, m->triangles[i].v2, m->triangles[i].v1, m);
		if(neighbor != -1) {
			table[i * 3 + 0] = neighbor;
		} else {
			table[i * 3 + 0] = -1;
		}
		neighbor = edge_table_find(et, m->triangles[i].v3, m->triangles[i].v2, m);
		if(neighbor != -1) {
			table[i * 3 + 1] = neighbor;
		} else {
			table[i * 3 + 1] = -1;
		}
		neighbor = edge_table_find(et, m->triangles[i].v1, m->triangles[i].v3, m);
		if(neighbor != -1) {
			table[i * 3 + 2] = neighbor;
		} else {
			table[i * 3 + 2] = -1;
		}
	}

	edge_table_dispose(et);
	return table;
}

#endif
