#include <stdlib.h>
#include <stdio.h>
#include "../TP3/include/hash_tables.h"
#include "assert.h"
#include "../TP3/include/mesh_adjacency.h"

int edge_pos_in_tri(int v1, int v2, struct Triangle t)
{
	for (int i = 0; i < 3; i ++){
		if ((v1 == t.idx[i])&&(v2 == t.idx[(i+1)%3]))
			return i;
	}
	return -1;
}

int tris_are_neighbors(int tri1, int tri2,const struct Mesh* m)
{
	for (int i = 0; i < 3; i++){
		if(edge_pos_in_tri(m->triangles[tri1].idx[(i+1)%3],m->triangles[tri1].idx[i],m->triangles[tri2]) != -1)
			return i;
	}
	return -1;
}

int *build_adjacency_table1(const struct Mesh* m)
{
	int *adj = (int*)malloc(3*(m->ntri)*sizeof(int));
	for (int i = 0; i < m->ntri; i ++){
		for (int k = 3 * i; k < 3 * (i + 1); k ++){
			adj[k] = -1;
		}
		for (int j = i + 1; j < m->ntri; j ++){
			int t = tris_are_neighbors(i, j, m);
			int u = tris_are_neighbors(j, i, m);
			if (t != -1){
				adj[3 * i + t] = 3 * j + u;
				adj[3 * j + u] = 3 * i + t;
			}
		}
	}
	return adj;
}

struct HashTable *build_edge_table1(const struct Mesh* m)
{
	HashTable* ht = hash_table_init(6*m->ntri, sizeof(Edge), 2*sizeof(int));
	for (int i = 0; i < m->ntri; i ++){
		for (int j = 0; j < 3; j++){
			struct Edge v;
			v.v1 = m->triangles[i].idx[j];
			v.v2 = m->triangles[i].idx[(j + 1) % 3];
			assert (hash_table_find(ht, &v) == NULL);
			hash_table_insert(ht, &v, &i);
		}
	}
	return ht;
}

int *build_adjacency_table2(const struct Mesh* m)
{
	int* adj = (int *)malloc(3 * m->ntri * sizeof(int));
	struct HashTable* ht = build_edge_table1(m);
	for (int i = 0; i < m->ntri; i ++){
		for (int j = 0; j < 3; j ++){
			struct Edge e;
			e.v2 = m->triangles[i].idx[j];
			e.v1 = m->triangles[i].idx[(j + 1) % 3];
			if (hash_table_find(ht, &e) == NULL){
				adj[3 * i + j] = *(int *)hash_table_find(ht, &e);
			}else{
				adj[3 * i + j] = -1;
			}
		}
	}
	return adj;
}

void edge_table_initialize(struct EdgeTable* et, int nvert, int ntri)
{
	et->head = (int*)malloc(nvert * sizeof(int));
	et->next = (int*)malloc(3 * ntri * sizeof(int));
}

void edge_table_dispose(struct EdgeTable* et)
{
	free(et->head);
	et->head = NULL;
	free(et->next);
	et->next = NULL;
}

void edge_table_insert(int v1, int edge_code, struct EdgeTable* et)
{
	int temp = 0;
	if (et->head[v1] == -1){
		et->head[v1] = edge_code;
	}else{
		temp = et->head[v1];

	}









