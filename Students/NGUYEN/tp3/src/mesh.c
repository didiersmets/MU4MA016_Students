#include <stdlib.h>

#include "mesh.h"

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

int edge_pos_in_tri (int v1 , int v2 , struct Triangle t){
    /* Returns the position of the v1->v2 edge in the triangle and -1 if it is not in the triangle.
    With convention : for a triangle whose vertices index list is a, b, c, the edge a->b has position 0, 
    the edge b->c has position 1, and the edge c->a has position 2.*/

    for (int i = 0; i < 3; i++){
        if ((t.idx[i] == v1)&&(t.idx[(i+1) % 3] == v2)){ // modulo 3 because indexes are cycling : 0->1->2->0 
            return i;
        }
    }
    return -1; 
}

int tris_are_neighbors (int tri1 , int tri2 , const struct Mesh *m){
    /* Returns the common edge between two triangles (with same convention, for tri1) and -1 otherwise.*/

    struct Triangle triangle1 = m->triangles[tri1];
    struct Triangle triangle2 = m->triangles[tri2];
	for (int i = 0; i < 3; i++){
		int v1 = triangle1.idx[i];
		int v2 = triangle1.idx[(i+1) % 3];
		if (edge_pos_in_tri(v2, v1, triangle2) != -1){
			return i;
		}
	}
    return -1;
}

int *build_adjacency_table1 (const struct Mesh *m){
    /* Returns address of the adjacency table of all triangles in the mesh.*/
    int *adj = malloc(3 * m->ntri * sizeof(int));
    memset(adj, -1, 3 * m->ntri * sizeof(int)); // fill ajd with -1

    for (int i = 0; i < m->ntri; i++){
        for (int j = 0; j < m->ntri ;j++){
            if (i == j)
				continue;
			int neighbouring_edge = tris_are_neighbors(i, j, m);
			if (neighbouring_edge != -1){
				adj[i * 3 + neighbouring_edge] = j; 
			}
        }
    }
    return adj;
}



