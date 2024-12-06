#include <stdio.h>
#include <stdlib.h>

#include "/root/MU4MA016_Students/ADrieux/TP3/include/mesh_adjacency.h"
#include "/root/MU4MA016_Students/ADrieux/TP3/include/mesh.h"
#include "/root/MU4MA016_Students/ADrieux/TP3/include/hash_tables.h"

int edge_pos_in_tri(int v1, int v2, struct Triangle t)
{
	if ((t.idx[0] == v1) && (t.idx[1] == v2))
	{
		return 0;
	}
	if ((t.idx[1] == v1) && (t.idx[2] == v2))
	{
		return 1;
	}
	if ((t.idx[2] == v1) && (t.idx[0] == v2))
	{ 
		return 2;
	}
	else {
		return -1;
	}
}

int tris_are_neighbors(int tri1, int tri2, const struct Mesh *m)
{
	if (edge_pos_in_tri(m->triangles[tri1].idx[1], m->triangles[tri1].idx[0], m->triangles[tri2]) != -1)
	{
		return(edge_pos_in_tri(m->triangles[tri1].idx[0], m->triangles[tri1].idx[1], m->triangles[tri1]));
	}
	if (edge_pos_in_tri(m->triangles[tri1].idx[2], m->triangles[tri1].idx[1], m->triangles[tri2]) != -1)
	{
		return(edge_pos_in_tri(m->triangles[tri1].idx[1], m->triangles[tri1].idx[2], m->triangles[tri1]));
	}
	if (edge_pos_in_tri(m->triangles[tri1].idx[0], m->triangles[tri1].idx[2], m->triangles[tri2]) != -1)
	{
		return(edge_pos_in_tri(m->triangles[tri1].idx[2], m->triangles[tri1].idx[0], m->triangles[tri1]));
	}
	else {
		return -1;
	}
}

int *build_adjacency_table1(const struct Mesh *m)
{
	int *adj = (int *)malloc(3*m->ntri*sizeof(int));
	for (int i = 0; i<m->ntri; i++)
	{
		for (int k = 0; k<m->ntri; k++)
		{
			if (tris_are_neighbors(i, k, m) != -1)
			{
				adj[3*i + tris_are_neighbors(i, k, m)] = k;
			} else {
				adj[3*i + tris_are_neighbors(i, k, m)] = -1;
			}
		}
	}
	return adj;
}

struct HashTable *build_edge_table1(const struct Mesh *m)
{
	struct HashTable *ht = hash_table_init(2*m->ntri, sizeof(struct Edge), sizeof(int));
	for (int i = 0; i<m->ntri; i++)
	{
		struct Triangle t = m->triangles[i];
		struct Edge edges[3] = {{t.idx[0],t.idx[1]}, {t.idx[1], t.idx[2]}, {t.idx[2], t.idx[0]}};
		hash_table_insert(ht, &edges[0], &i);
		hash_table_insert(ht, &edges[1], &i);
		hash_table_insert(ht, &edges[2], &i);
	}
	return(ht);
}

int *build_adjacency_table2(const struct Mesh *m)
{
	int *adj = (int *)malloc(3*m->ntri*sizeof(int));
	struct HashTable *ht = build_edge_table1(m);
	for (int i = 0; i<m->ntri; i++)
	{
		struct Triangle t = m->triangles[i];
		struct Edge edges[3] = {{t.idx[0],t.idx[1]}, {t.idx[1], t.idx[2]}, {t.idx[2], t.idx[0]}};
		for (int j = 0; j<3; j++)
		{
			struct Edge opposite_edge;
			edges[j].v2;
			edges[j].v1;
			opposite_edge = edges[j];
			if (hash_table_find(ht, &opposite_edge) != NULL)
			{
				int *val = (int *)hash_table_find(ht, &opposite_edge);
				adj[3*i+j] = *val;
			}else {
				adj[3*i + j] = -1;
			}
		}
	}
	hash_table_fini(ht);
	return adj;
}

void edge_table_initialize(struct EdgeTable *et, int nvert, int ntri)
{
	et->head = (int *)malloc(nvert*sizeof(int));
	et->next = (int *)malloc(3*ntri*sizeof(int));
}

void edge_table_dispose(struct EdgeTable *et)
{
	free(et->head);
	free(et->next);
}

void edge_table_insert(int v1, int edge_code, struct EdgeTable *et)
{
	int tmp = 0;
	if (et->head[v1] == -1)
	{
		et->head[v1] = edge_code;
	} else {
		tmp = et->head[v1];
		et->head[v1] = edge_code;
		et->next[edge_code] = tmp;
	}
}

int edge_table_find(int v1, int v2, const struct EdgeTable *et, const struct Mesh *m)
{
	int edge_code = et->head[v1];
	while (edge_code != -1)
	{
		int tri_idx = edge_code/3;
		if (edge_pos_in_tri(v1, v2, m->triangles[tri_idx]) != -1)
		{
			return tri_idx;
		} else {
			edge_code = et->next[edge_code];
		}
	}
	return -1;
}

struct EdgeTable *build_edge_table3(const struct Mesh *m)
{
	struct EdgeTable *et = (struct EdgeTable *)malloc(sizeof(struct EdgeTable));
	edge_table_initialize(et, m->nvert, m->ntri);
	for (int i=0; i<m->ntri; i++)
	{
		struct Triangle t = m->triangles[i];
		edge_table_insert(t.idx[0], 3*i, et);
		edge_table_insert(t.idx[1], 3*i+1, et);
		edge_table_insert(t.idx[2], 3*i+2, et);
	}
	return(et);
}

int *build_adjacency_table3(const struct Mesh *m)
{
	int *adj = (int *)malloc(3*m->ntri*sizeof(int));
	struct EdgeTable *et = build_edge_table3(m);
	for (int i = 0; i<m->ntri; i++)
	{
		struct Triangle t = m->triangles[i];
		struct Edge edges[3] = {{t.idx[0],t.idx[1]}, {t.idx[1], t.idx[2]}, {t.idx[2], t.idx[0]}};
		for (int j = 0; j<3; j++)
		{
			adj[3*i + j] = edge_table_find(edges[j].v2, edges[j].v1, et, m);
		}
	}
	edge_table_dispose(et);
	return adj;
}







