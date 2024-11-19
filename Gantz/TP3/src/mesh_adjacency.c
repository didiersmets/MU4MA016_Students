#include <stdlib.h>
#include "../include/mesh.h"
#include "../include/hash_tables.h"
#include "../include/mesh_adjacency.h"

int edge_pos_in_tri(int v1, int v2, struct Triangle t){
	if(t.v1==v1 && t.v2==v2) return 0;
	if(t.v2==v1 && t.v3==v2) return 1;
	if(t.v3==v1 && t.v1==v2) return 2;
	return -1;
}

int tris_are_neighbors(int tri1, int tri2, const struct Mesh *m){
	struct Triangle t1 = m->triangles[tri1];
	struct Triangle t2 = m->triangles[tri2];
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
	struct HashTable* ht = (struct HashTable*) hash_table_init(3*(m->ntri), sizeof(struct Edge), sizeof(int));
	// Loop over all triangles and their edges
	for(int i=0; i<m->ntri; i++){
		struct Triangle t = (m->triangles)[i];
		for(int j=0; j<3; j++){
			struct Edge e;
			e.v1 = t.idx[j%3];
			e.v2 = t.idx[(j+1)%3];
			hash_table_insert(ht,&e,&i); 	
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
		struct Triangle t = (m->triangles)[i];
		for(int j=0; j < 3; j++){
			struct Edge* e = (struct Edge*) malloc(sizeof(struct Edge));
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

void edge_table_initialize(struct EdgeTable *et, int nvert, int ntri){
	et->head = (int*) malloc(nvert*sizeof(int));
	for(int i=0; i<nvert; i++){
		et->head[i]=-1;
	}
	et->next = (int*) malloc(3*ntri*sizeof(int));
	for(int i=0; i<3*ntri; i++){
		et->next[i]=-1;
	}
}

void edge_table_dispose(struct EdgeTable *et){
	free(et->head);
	free(et->next);
	free(et);
}

void edge_table_insert(int v1, int edge_code, struct EdgeTable *et){
	int* h = et->head;
	int* n = et->next;
	if(h[v1]==-1){
		h[v1] = edge_code;
	} else {
		int tmp = h[v1];
		h[v1] = edge_code;
		n[edge_code] = tmp;
	}
}

int edge_table_find(int v1, int v2, const struct EdgeTable *et, const struct Mesh *m){
	int *h = et->head;
	int *n = et->next;
	struct Triangle *tri = m->triangles;
	
	int edge_code = h[v1];
	if(edge_code==-1) return -1;
	int i = edge_code/3;
	int j = edge_code%3;

	if((tri[i]).idx[(j+1)%3]==v2){
		return edge_code;
	} else {
		while(edge_code!=-1){
			edge_code = n[edge_code];
			int i = edge_code/3;
			int j = edge_code%3;
			if((tri[i]).idx[(j+1)%3]==v2) return edge_code;
		}
	}
	return -1;
}

struct EdgeTable *build_edge_table3(const struct Mesh *m){
	struct EdgeTable *et = (struct EdgeTable*) malloc(sizeof(struct EdgeTable)); 
	edge_table_initialize(et, m->nvert, m->ntri);
	// Loop over all triangles and their edges
	for(int i=0; i<m->ntri; i++){
		struct Triangle t = (m->triangles)[i];
		for(int j=0; j<3; j++){
			struct Edge e;
			e.v1 = t.idx[j];
			edge_table_insert(e.v1,3*i+j,et); 	
		}
	}
	return et;
}

int *build_adjacency_table3(const struct Mesh *m){
	struct EdgeTable *et = build_edge_table3(m);	
	int* adj = (int*) malloc(3*(m->ntri)*sizeof(int));
	for(int k=0; k<3*(m->ntri); k++){
		adj[k] = -1;
	}
	for(int i=0; i < m->ntri; i++){
		struct Triangle t = (m->triangles)[i];
		for(int j=0; j < 3; j++){
			// ! opposite edge
			int v2 = t.idx[j%3];
			int v1 = t.idx[(j+1)%3];	
			int edge_code = edge_table_find(v1,v2,et,m);
			adj[3*i+j] = edge_code/3;
		}
	}
	edge_table_dispose(et);
	return adj;
}


