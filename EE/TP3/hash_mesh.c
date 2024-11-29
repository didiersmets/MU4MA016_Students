#include <stdlib.h>
#include <stdio.h>
#include <FILE.h>
#include "hash_tables.h"

struct Vertex{
	union{
		struct{
			double x, y;
		};
		double coord[2];
	};
};

struct Triangle{
	union{
		struct{
			int A, B, C;
		};
		int idx[3];
	};
};

struct Mesh2D{
	int nv; /*number of vertices in the mesh*/
	struct Vertex* vert;/*array of vertices*/
	int nt; /*number of triangles*/
	struct Triangle* tri; /*array of triangles*/
};

struct Edge{
	int v1;
	int v2;
};

int initialise_mesh2D(int vtx_capacity, int tri_capacity)
{
	struct Mesh2D* m = (struct Mesh2D*)malloc(sizeof(Mesh2D));
	m->nv = vtx_capacity;
	m->vert = (struct Vertex*)malloc(vtx_capacity*sizeof(struct Vertex));
	m->nt = tri_capacity;
	m->tri = (struct Triangle*)malloc(tri_capacity*sizeof(struct Triangle));
	return 0;
}

void dispose_mesh2D(struct Mesh2D* m)
{
	free(m->vert);
	free(m->tri);
}

double area_mesh2D(struct Mesh2D* m)
{
	double res = 0;
	for (int i = 0; i < m->nt; i++){
		struct Vertex v1 = m->vert[m->tri[i].A];
		struct Vertex v2 = m->vert[m->tri[i].B];
		struct Vertex v3 = m->vert[m->tri[i].C];
		res += ((v1.x - v2.x) * (v3.y - v2.y) - (v1.y - v2.y) * (v3.x - v1.x))/2;
	}
	return res;
}

int edge_pos_in_tri(int v1, int v2, struct Triangle t)
{
	for (int i = 0; i < 3; i ++){
		if (v1 == t.idx[i])&&(v2 == t.idx[(i+1)%3])
			return i;
	}
	return -1;
}

int tris_are_neighbors(int tri1, int tri2, struct Mesh2D* m)
{
	for (int i = 0; i < 3; i++){
		if(edge_pos_in_tri(m->tri[tri1].idx[(i+1)%3],m->tri[tri].idx[i],m->tri[tri2]) != -1)
			return i;
	}
	return -1;
}

int *build_adjacency_table1(const struct Mesh* m)
{
	int *adj = malloc(3*m->nt*size(int));
	for (int i = 0; i < m->nt; i ++){
		for (int k = 3 * i; k < 3 * (i + 1); k ++){
			adj[k] = -1;
		}
		for (int j = i + 1; j < m->nt; j ++){
			t = tris_are_neighbors(m->tri[i], m->tri[j], m);
			u = tris_are_neighbors(m->tri[j], m->tri[i], m);
			if (t != -1){
				agj[3 * i + t] = j;
				adj[3 * j + u] = i;
			}
		}
	}
	return adj;
}

struct HashTable *build_edge_table1(const struct Mesh2D* m)
{
