#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>


#include "/root/MU4MA016_Students/NARANJO/TP2/tri_mesh.c"

int edge_pos_in_tri ( int v1 , int v2 , struct Triangle t )
{
	if (v1 == t.alpha && v2 == t.beta){
		return 0;
	}
	if  (v1 == t.beta && v2 == t.gamma){
                return 1;
        }
	if (v1 == t.gamma && v2 == t.alpha){
                return 2;
        }
	else{
		return -1;
	}
}


int tris_are_neighbors(int tri1, int tri2, const struct Mesh *m)
{
	struct Vertex v1 = m->vert[(tri1.alpha)];
	struct Vertex v2 = m->vert[(tri1.beta)];
	struct Vertex v3 = m->vert[(tri2.gamma)];

	if (edge_pos_in_tri(v1, v2, tri2) != -1){
		return edge_pos_in_tri(v1, v2, tri2);
	}

	if (edge_pos_in_tri(v2, v3, tri2) != -1){
                return edge_pos_in_tri(v2, v3, tri2);
        }

	if (edge_pos_in_tri(v3, v1, tri2) != -1){
                return edge_pos_in_tri(v3, v1, tri2);
        }

	else{
		return -1;
	}
}

int *build_adjacency_table1(const struct Mesh *m)
{
	int adj[3*m->nt];
	for(int i = 0; i< 3*m->nt, i++){
		adj[i] = -1;
	}

	for (int i = 0; i < m->nt, i++){
		struct Triangle tri = m->tri[i];
		for (int j = 0; j < 2; j++){
			for (int k = 0; k < m->nt, k++){
				struct Triangle tri2 = m->tri[k];
				if (i != k && tris_are_neighbors(tri, tri2, m != -1)){
					adj[3*i + j] = tris_are_neighbors(tri, tri2, m != -1);
				}
			
			}

		}
	}
	return adj;
		


}




