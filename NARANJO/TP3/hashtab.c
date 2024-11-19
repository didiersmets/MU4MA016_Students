#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>


#include "../MU4MA016_Students/TP3/include/hash_tables.h"
#include "../MU4MA016_Students/TP3/include/mesh.h"


int edge_pos_in_tri ( int v1 , int v2 , struct Triangle t )
{
	if (v1 == t.v1 && v2 == t.v2){
		return 0;
	}
	if  (v1 == t.v2 && v2 == t.v3){
                return 1;
        }
	if (v1 == t.v3 && v2 == t.v1){
                return 2;
        }
	else{
		return -1;
	}
}


int tris_are_neighbors(int tri1, int tri2, const struct Mesh *m)
{
	struct Vertex v1 = m->vert[(tri1.v1)];
	struct Vertex v2 = m->vert[(tri1.v2)];
	struct Vertex v3 = m->vert[(tri2.v3)];

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
	int adj[3*m->ntri];
	for(int i = 0; i< 3*m->ntri; i++){
		adj[i] = -1;
	}

	for (int i = 0; i < m->ntri; i++){
		struct Triangle tri = m->triangles[i];
		for (int j = 0; j < 2; j++){
			for (int k = 0; k < m->ntri; k++){
				struct Triangle tri2 = m->triangles[k];
				if (i != k && tris_are_neighbors(tri, tri2, m) != -1){
					adj[3*i + j] = tris_are_neighbors(tri, tri2, m != -1);
				}
			
			}

		}
	}
	return adj;
}




int main(){


    	struct Mesh2D* mesh = initialize_mesh2D(5, 2);

    	
    	mesh->vert[0] = (struct Vertex) {0.0, 0.0};
    	mesh->vert[1] = (struct Vertex) {1.0, 0.0};
    	mesh->vert[2] = (struct Vertex) {1.0, 1.0};
    	mesh->vert[3] = (struct Vertex) {0.0, 1.0};
    	mesh->vert[4] = (struct Vertex) {0.5, 0.5};
    	mesh->tri[0] = (struct Triangle) {0, 1, 4}; 
    	mesh->tri[1] = (struct Triangle) {1, 2, 4}; 

    	dispose_mesh2D(mesh);

	int adj = *build_adjacency_table1;
	printf(adj);

    	return 0;
}

