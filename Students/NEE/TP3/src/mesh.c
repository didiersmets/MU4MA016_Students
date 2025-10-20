#include <stdlib.h>
#include <stdio.h>
#include "mesh.h"
#include <string.h>
#include "mesh_adjacency.h"  

void initialize_mesh(struct Mesh *m)
{
	m->nvert = 0;
	m->ntri = 0;
	m->vertices = NULL;
	m->triangles = NULL;
}

void dispose_mesh(struct Mesh *m)
{
	m->nvert = 0;
	m->ntri = 0;
	free(m->vertices);
	m->vertices = NULL;
	free(m->triangles);
	m->triangles = NULL;
}

int edge_pos_in_tri(int v1, int v2, struct Triangle t)
{
	// Return position of edge in triangle, or -1 if edge not in triangle
	// We check if the
	for (int i = 0; i < 3; i++)
	{

		if (t.idx[i] == v1 && t.idx[(i + 1) % 3] == v2)
		{
			return i;
		}
	}
	return -1;
}

int tris_are_neighbors(int tri1, int tri2, const struct Mesh *m)
{
	// go through each of the vertices in the first one. check if that vertex if in the second one. check if first triangle vertx +1 = secon triangle vertex - 1
	struct Triangle triangle_1 = m->triangles[tri1];
	struct Triangle triangle_2 = m->triangles[tri2];
	for (int i = 0; i < 3; i++)
	{

		int v1 = triangle_1.idx[i];
		int v2 = triangle_1.idx[(i + 1) % 3];
		if (edge_pos_in_tri(v2, v1, triangle_2) != -1)
		{
			return i;
		}
	}
	return -1;
}

int *build_adjacency_table1(const struct Mesh *m)
{
	int *adj = malloc(3 * m->ntri * sizeof(int));
	memset(adj, -1, 3 * m->ntri * sizeof(int));
	for (int first_tri_ind = 0; first_tri_ind < m->ntri; first_tri_ind++)
	{
		for (int second_tri_ind = 0; second_tri_ind < m->ntri; second_tri_ind++)
		{
			if (first_tri_ind == second_tri_ind)
				continue;
			int neighbouring_edge = tris_are_neighbors(first_tri_ind, second_tri_ind, m);
			if (neighbouring_edge != -1)
			{
				adj[first_tri_ind * 3 + neighbouring_edge] = second_tri_ind;
			}
		}
	}
	return adj;
}



struct HashTable *build_edge_table_1(const struct Mesh *m)
{
	struct HashTable *dict = hash_table_init(m->ntri * 3, sizeof(struct Edge), sizeof(int));
	// now i loop through all triangles, and i add all edges to my hash table, with value triangle position
	for (int tri_ind = 0; tri_ind < m->ntri; tri_ind++)
	{
		for (int edge_ind = 0; edge_ind < 3; edge_ind++)
		{
			struct Edge e = {
				m->triangles[tri_ind].idx[edge_ind],
				m->triangles[tri_ind].idx[(edge_ind + 1) % 3]};
			hash_table_insert(dict, &e, &tri_ind);
		}
	}
	return dict;
}

int *build_adjacency_table2(const struct Mesh *m)
{
	int *adj = malloc(3 * m->ntri * sizeof(int));
	memset(adj, -1, 3 * m->ntri * sizeof(int));
	// create hashtable
	struct HashTable *dict = build_edge_table_1(m);

	// now, the objective is to go through all the triangles, and if the has table returns another triangle for the reverse order,
	for (int tri_ind = 0; tri_ind < m->ntri; tri_ind++)
	{
		for (int edge_ind = 0; edge_ind < 3; edge_ind++)
		{
			struct Edge reverse_e = {
				m->triangles[tri_ind].idx[(edge_ind + 1) % 3],
				m->triangles[tri_ind].idx[edge_ind]};
			int *neighbour = hash_table_find(dict, &reverse_e);
			if (neighbour != NULL)
			{
				adj[tri_ind * 3 + edge_ind] = *neighbour;
			}
		}
	}
	// free hash table memory
	hash_table_fini(dict);
	return adj;
}



void edge_table_initialize(struct EdgeTable *et, int nvert, int ntri)
{
	et->head = malloc(nvert * sizeof(int));
	memset(et->head, -1, nvert * sizeof(int));
	et->next = malloc(3 * ntri * sizeof(int)); // this size because its
	memset(et->next, -1, 3 * ntri * sizeof(int));
}

void edge_table_dispose(struct EdgeTable *et)
{
	free(et->head);
	free(et->next);
	free(et);
}

void edge_table_insert(int v1, int edge_code, struct EdgeTable *et)
{
	// First, we check if v1 is occupied
	// if its -1, its not occupied, and w simply place edge_code there
	if (et->head[v1] == -1)
	{
		et->head[v1] = edge_code;
	}
	else
	{
		// head is occupied( were not dealing with possible deletion here)
		int tmp = et->head[v1];
		et->head[v1] = edge_code;
		et->next[edge_code] = tmp;
	}
}

int edge_table_find(int v1, int v2, const struct EdgeTable *et, const struct Mesh *m)
{
	// this is more complicated, we need to
	// return -1 if not there
	// First of all: check head v1. If head[v1] == -1, we return -1;
	int edge_code = et->head[v1];

	while (edge_code != -1)
	{
		// what we need to do here is the following: v2 is not encoded in the has table, so we
		// calculate the triangle based on the code, and we can check if v2 is correct
		int triangle_idx = edge_code / 3;
		int edge_position = edge_code % 3;
		int vertex1 = m->triangles[triangle_idx].idx[edge_position];
		int vertex2 = m->triangles[triangle_idx].idx[(edge_position + 1) % 3];

		// we check check if this is the edge we're looking for
		if (vertex1 == v1 && vertex2 == v2)
		{
			return edge_code; // found
		}
		// not found, we move on
		edge_code = et->next[edge_code];
	}
	return -1;
}

struct EdgeTable *build_edge_table_3(const struct Mesh *m)
{
	// We simply loop through all the triangles and insert
	struct EdgeTable *et = malloc(sizeof(struct EdgeTable));

	// check if allcoated correctly (not actually gonnna check but I know i should)
	edge_table_initialize(et, m->nvert, m->ntri);

	for (int i = 0; i < m->ntri; i++)
	{
		// we loop through every edge in every tri, add to edge table
		for (int j = 0; j < 3; j++)
		{
			edge_table_insert(m->triangles[i].idx[j], i * 3 + j, et);
		}
	}

	return et;
}

int *build_adjacency_table3(const struct Mesh *m)
{
	int *adj_table = malloc(3 * m->ntri * sizeof(int));
	memset(adj_table, -1, 3 * m->ntri * sizeof(int));
	// check if allcoated correctly (not actually gonnna check but I know i should)
	// now we loop through all edges like before, but do edgetable find and insert value
	struct EdgeTable *et = build_edge_table_3(m);

	for (int i = 0; i < m->ntri; i++)
	{
		// we loop through every edge in every tri, add to edge table
		for (int j = 0; j < 3; j++)
		{
			int vertex1 = m->triangles[i].idx[j];
			int vertex2 = m->triangles[i].idx[(j + 1) % 3];
			int reverse_edge_code = edge_table_find(vertex2, vertex1, et, m); // reverse order! (divide by 3 to get triangle index)
			if (reverse_edge_code != -1)
			{
				adj_table[i * 3 + j] = reverse_edge_code / 3;
			}
		}
	}
	edge_table_dispose(et);
	return adj_table;
}