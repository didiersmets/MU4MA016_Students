#include <stdlib.h>
#include "mesh.h"
#include "hash_tables.h"
#include "mesh_adjacency.h"

int edge_pos_in_tri(int v1, int v2, struct Triangle t){
	if(t.v1==v1 && t.v2==v2) return 0;
	if(t.v2==v1 && t.v3==v2) return 1;
	if(t.v3==v1 && t.v1==v2) return 2;
	return -1;
}

int tris_are_neighbors(int tri1, int tri2, const struct Mesh *m){
	Triangle t1 = m->triangles[tri1];
	Triangle t2 = m->triangles[tri2];
	for(int i=0; i<3; i++){
		int v1 = t2.idx[(i+1)%3];
		int v2 = t2.idx[(i+1)%3];
		int pos = edge_pos_in_tri(v1,v2,t1);
		if(pos!=-1) return pos;
	}
	return -1;
}

int* build_adjacency_table1(const struct Mesh *m){
	int* adj = (int*) malloc(3*(m->ntri)*sizeof(int));
	for(int k=0; k<3*(m->ntri); k++){
		adj[k] = -1;
	}
	for(int i=0; i < m->ntri; i++){
		for(int j=0; j < m->ntri; j++){
			int t1_edge = tris_are_neighbors(i,j,m);
			if(t1_edge!=-1) adj[3*i+t1_edge] = j;
		}
	}
	return adj;
}

struct HashTable* build_edge_table1(const struct Mesh *m){
	struct HashTable* ht = (struct HashTable*) hash_table_init(3*(m->ntri), sizeof(Edge), sizeof(int));
	// Loop over all triangles and their edges
	for(int i=0; i<m->ntri; i++){
		Triangle t = (m->triangles)[i];
		for(int j=0; j<3; j++){
			Edge* e = (Edge*) malloc(sizeof(Edge));
			e->v1 = t.idx[j%3];
			e->v2 = t.idx[(j+1)%3];
			hash_table_insert(ht,e,&i); 	
		}
	}
	return ht;
}

int* build_adjacency_table2(const struct Mesh *m){
	struct HashTable* et = build_edge_table1(m);	
	int* adj = (int*) malloc(3*(m->ntri)*sizeof(int));
	for(int k=0; k<3*(m->ntri); k++){
		adj[k] = -1;
	}
	for(int i=0; i < m->ntri; i++){
		Triangle t = (m->triangles)[i];
		for(int j=0; j < 3; j++){
			Edge* e = (Edge*) malloc(sizeof(Edge));
			// ! opposite edge
			e->v2 = t.idx[j%3];
			e->v1 = t.idx[(j+1)%3];	
			int* val_ptr = (int*) hash_table_find(et,e);
			adj[3*i+j] = *val_ptr;
		}
	}
	free(et);
	return adj;
}




