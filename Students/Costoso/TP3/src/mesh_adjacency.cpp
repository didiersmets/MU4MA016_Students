#include "mesh_adjacency.h"

int edge_pos_in_tri(int v1, int v2, struct Triangle t) {
	if ((v1 == t.v1 && v2 == t.v2)) { return 0; }
	else if ((v1 == t.v2 && v2 == t.v3)) { return 1; }
	else if ((v1 == t.v1 && v2 == t.v3)) { return 2; }
	else { return -1; }
}

int tris_are_neighbors(int tri1, int tri2, const struct Mesh* m) {
	struct Triangle t1 = m->triangles[tri1];

	if( m->triangles[tri1].v1 == m->triangles[tri2].v1 && m->triangles[tri1].v2 == m->triangles[tri2].v2) return edge_pos_in_tri(m->triangles[tri1].v1, m->triangles[tri1].v2, m->triangles[tri1]);
	if( m->triangles[tri1].v2 == m->triangles[tri2].v2 && m->triangles[tri1].v3 == m->triangles[tri2].v3) return edge_pos_in_tri(m->triangles[tri1].v2, m->triangles[tri1].v3, m->triangles[tri1]);
	if( m->triangles[tri1].v3 == m->triangles[tri2].v3 && m->triangles[tri1].v1 == m->triangles[tri2].v1) return edge_pos_in_tri(m->triangles[tri1].v3, m->triangles[tri1].v1, m->triangles[tri1]);
	return -1;
}

int* build_adjacency_table1(const struct Mesh* m) {
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




void edge_table_initialize(struct EdgeTable *et, int nvert, int ntri){
	et->head = malloc(sizeof(int) * nvert);
	et->next = malloc(sizeof(int) * 3 * ntri);
	for(int i = 0; i < nvert; i++){
		head[i]=-1;
	}
	for(int i = 0; i < 3 * ntri; i++){
		next[i]=-1;
	}
}

void edge_table_dispose(struct EdgeTable *et){
	free(et->head);
	free(et->next);
}

void edge_table_insert(int v1, int edge_code, struct EdgeTable *et){
	if(et->head[v1] == -1){
		et->h[v1] = edge_code;
	}
	else{
		int tmp = et->h[v1];
		et->h[v1] = edge_code;
		et->next[edge_code] = tmp;
	}
}

int  edge_table_find(int v1, int v2, const struct EdgeTable *et, const struct Mesh *m){
	int triangle = et->h[v1]/3;
	int edge = et->h[v1]%3;
	if(edge_pos_in_tri(v1, v2, m->triangles[triangle]) == edge){
		return et->h[v1];
	}
	else{
		int next_code = h[v1];
		while(et->next[next_code] != -1){
			triangle = et->next[next_code]/3;
			edge = et->next[next_code]%3;
			if(edge_pos_in_tri(v1, v2, m->triangles[triangle]) == edge){
				return et->next[next_code];
			}
		}
	}
	return -1;
}

struct EdgeTable *build_edge_table3(const struct Mesh *m){
	struct EdgeTable *Result;
	edge_table_initialize(Result, m->nvert, m->ntri);
	for(int i = 0; i < m->ntri; i++){
		int v1 = m->triangle[i].v1;
		int v2 = m->triangle[i].v2;
		int v3 = m->triangle[i].v3;
		int edge_code = 3 * i + edge_pos_in_tri(v1, v2, m->triangle[i]);
		edge_table_insert(v1, edge_code, Result);
		int edge_code = 3 * i + edge_pos_in_tri(v2, v3, m->triangle[i]);
		edge_table_insert(v2, edge_code, Result);
		int edge_code = 3 * i + edge_pos_in_tri(v3, v1, m->triangle[i]);
		edge_table_insert(v3, edge_code, Result);
	}
	return Result;
}

int *build_adjacency_table3(const struct Mesh *m){
	int* adj = (int*)malloc(sizeof(int) * 3 * m->ntri);
	struct EdgeTable* H = build_edge_table3(m);
	for (int i = 0; i < 3 * m->ntri; i++) {
		adj[i] = -1;
	}
	for (int i = 0; i < m->ntri; i++) {
		struct Edge key;
		
		key.v1 = m->triangles[i].v2;
		key.v2 = m->triangles[i].v1;
		if(edge_table_find(key.v1, key.v2, H, m) != -1){
			adj[(3 * i)] = edge_table_find(H, &key) % 3;
		}

		key.v1 = m->triangles[i].v3;
		key.v2 = m->triangles[i].v2;
		if(edge_table_find(key.v1, key.v2, H, m) != -1){
			adj[(3 * i) + 1] = edge_table_find(H, &key) % 3;
		}

		key.v1 = m->triangles[i].v1;
		key.v2 = m->triangles[i].v3;
		if(edge_table_find(key.v1, key.v2, H, m) != -1){
			adj[(3 * i) + 2] = edge_table_find(H, &key) % 3;
		}
	}
	return adj;
}
