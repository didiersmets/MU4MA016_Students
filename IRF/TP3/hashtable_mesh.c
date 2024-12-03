#include <stdio.h>
#include <stdlib.h>
#include "include/mesh_adjacency.h"
#include "include/mesh.h"

int edge_pos_in_tri(int v1, int v2, struct Triangle t)
{
	if ((t.idx[0] == v1) && (t.idx[1] == v2)){
		return 0;
	}
	if ((t.idx[1] == v1) && (t.idx[2] == v2)){
		return 1;
	}
	if ((t.idx[2] == v1) && (t.idx[0] == v2)){
		return 2;
	}
	else {
		return -1;
	}
}

int tris_are_neighbors(int tri1, int tri2, const struct Mesh *m)
{
	int *idx = 
	for (int i = 0; i<3; i++){
		int *idx1 = m->triangles[tri1].idx[(i+1)%3];
		int *idx2 = m->triangles[tri1].idx[i]
		if (edge_pos_in_tri(idx1, idx2, m->triangles[tri2]) != -1){
			return edge_pos_in_tri(idx2, idx1, m->triangles[tri1]);
		}	
	}
	return -1;
}

		










