#include <stdlib.h>

#include "../include/mesh_adjacency.h"
#include "../src/mesh.c"

int edge_pos_in_tri(int v1,int v2, struct Triangle t)
{
	for(int i=0;i<2;i++){
		if(v1 == t[i%3] && v2 == t[(i+1)%3]){
			return i;
		}
	}
	return -1;
}

int tris_are_neighbors(int tri1,int tri2,const struct Mesh *m)
{
	struct Triangle* t1 =&m->triangles[tri1];
	struct Triangle* t2 = &m->triangles[tri2];
	for(int i=0;i<2;i++){
		int v1 = t2[i%3];
		int v2 = t2[(i+1)%3];
		int common_posi = edge_pos_in_tri(v1,v2,t1);
		if(common_posi != -1){
			return common_posi;
		}
	}
	return -1;
}

int *build_adjacency_table1(const struct Mesh *m)
{
	int adj[3*m->nt];

	return adj;
}
