#include "mesh.h"
#include "hash_tables.h"
#include "mesh_adjacency.h"

int edge_pos_in_tri(int v1, int v2, struct Triangle t) {
	if ((v1 == t.v1 && v2 == t.v2)) { return 0; }
	else if ((v1 == t.v2 && v2 == t.v3)) { return 1; }
	else if ((v1 == t.v1 && v2 == t.v3)) { return 2; }
	else { return -1; }
}

int tris_are_neighbors(int tri1, int tri2, const struct Mesh* m) {
	if( m->triangles[tri1].v1 == m->triangles[tri2].v1 && m->triangles[tri1].v2 == m->triangles[tri2].v2) return edge_pos_in_tri(m->triangles[tri1].v1, m->triangles[tri1].v2, m->triangles[tri1]);
	if( m->triangles[tri1].v2 == m->triangles[tri2].v2 && m->triangles[tri1].v3 == m->triangles[tri2].v3) return edge_pos_in_tri(m->triangles[tri1].v2, m->triangles[tri1].v3, m->triangles[tri1]);
	if( m->triangles[tri1].v3 == m->triangles[tri2].v3 && m->triangles[tri1].v1 == m->triangles[tri2].v1) return edge_pos_in_tri(m->triangles[tri1].v3, m->triangles[tri1].v1, m->triangles[tri1]);
	return -1;
}

int *build_adjacency_table1(const struct Mesh* m) {
	int* adj = (int*)malloc(sizeof(int) * 3 * m->ntri);
	for (int i = 0; i < 3 * m->ntri; i++) {
		adj[i] = -1;
	}
	for (int i = 0; i < m->ntri; i++) {
		for (int j = 0; j < m->ntri; j++) {
			if(tris_are_neighbors(i, j, m)!=-1){
				adj[(3 * i) + tris_are_neighbors(i, j, m)] = j;
			}
		}
	}
	return adj;
}

struct HashTable* build_edge_table1(const struct Mesh* m) {
	struct HashTable* H = hash_table_init((m->nvert) * (m->nvert), sizeof(struct Edge), sizeof(int));
	for(int i = 0; i < m->ntri; i++){
		struct Edge e;
	    int idx = i;
		e.v1 = m->triangles[i].v1;
		e.v2 = m->triangles[i].v2;
		hash_table_insert(H, &e, &idx);
		e.v1 = m->triangles[i].v2;
		e.v2 = m->triangles[i].v3;
		hash_table_insert(H, &e, &idx);
		e.v1 = m->triangles[i].v3;
		e.v2 = m->triangles[i].v1;
		hash_table_insert(H, &e, &idx);
	}
}

int* build_adjacency_table2(const struct Mesh* m) {
	int* adj = (int*)malloc(sizeof(int) * 3 * m->ntri);
	struct HashTable* H = build_edge_table1(m);
	for (int i = 0; i < 3 * m->ntri; i++) {
		adj[i] = -1;
	}
	for (int i = 0; i < m->ntri; i++) {
		struct Edge key;
		
		key.v1 = m->triangles[i].v2;
		key.v2 = m->triangles[i].v1;
		if(hash_table_find(H, &key) != NULL){
			adj[(3 * i)] = *hash_table_find(H, &key);
		}

		key.v1 = m->triangles[i].v3;
		key.v2 = m->triangles[i].v2;
		if(hash_table_find(H, &key) != NULL){
			adj[(3 * i) + 1] = *hash_table_find(H, &key);
		}

		key.v1 = m->triangles[i].v1;
		key.v2 = m->triangles[i].v3;
		if(hash_table_find(H, &key) != NULL){
			adj[(3 * i) + 2] = *hash_table_find(H, &key);
		}
	}
	return adj;
}