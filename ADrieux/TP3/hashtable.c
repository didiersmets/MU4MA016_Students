#include <stdio.h>
#include <stdlib.h>

#include "/users/home/28624202/MU4MA016_Students/TP3/include/mesh_adjacency.h"
#include "/users/home/28624202/MU4MA016_Students/TP3/include/mesh.h"
#include "/users/home/28624202/MU4MA016_Students/TP3/include/hash_tables.h"

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
	struct HashTable *ht = hash_table_init(






