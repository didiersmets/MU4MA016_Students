#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#include "hash_tables.c"
#include "mesh.c"

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
	struct Triangle t1 = m->triangles[tri1];
	struct Triangle t2 = m->triangles[tri2];

	if (edge_pos_in_tri(t1.v1, t1.v2, t2) != -1){
		return edge_pos_in_tri(t1.v1, t1.v2, t2);
	}

	if (edge_pos_in_tri(t1.v2, t1.v3, t2) != -1){
                return edge_pos_in_tri(t1.v2, t1.v3, t2);
        }

	if (edge_pos_in_tri(t1.v3, t1.v1, t2) != -1){
                return edge_pos_in_tri(t1.v3, t1.v1, t2);
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
		for (int j = 0; j < 2; j++){
			for (int k = 0; k < m->ntri; k++){
				if (i != k && tris_are_neighbors(i, k, m) != -1){
					adj[3*i + j] = tris_are_neighbors(i, k, m);
				}
			
			}

		}
	}
	return adj;
}




int main(){

	struct Mesh* mesh;
    	initialize_mesh(mesh);

    	
    	mesh->vertices[0] = (struct Vertex) {0.0, 0.0};
    	mesh->vertices[1] = (struct Vertex) {1.0, 0.0};
    	mesh->vertices[2] = (struct Vertex) {1.0, 1.0};
    	mesh->vertices[3] = (struct Vertex) {0.0, 1.0};
    	mesh->vertices[4] = (struct Vertex) {0.5, 0.5};
    	mesh->triangles[0] = (struct Triangle) {0, 1, 4}; 
    	mesh->triangles[1] = (struct Triangle) {1, 2, 4}; 

        dispose_mesh(mesh);

	int adj = build_adjacency_table1;
	printf(adj);

    	return 0;
}

