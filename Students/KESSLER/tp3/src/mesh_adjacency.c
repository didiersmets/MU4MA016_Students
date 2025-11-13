#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "mesh_adjacency.h"

int edge_pos_in_tri(int v1, int v2, struct Triangle t) {
    if (t.v1 == v1 && t.v2 == v2)
        return 0;
    if (t.v2 == v1 && t.v3 == v2)
        return 1;
    if (t.v3 == v1 && t.v1 == v2)
        return 2;
    
    return -1;
}

int tris_are_neighbors(int tri1, int tri2, const struct Mesh* m) {
    int result1, result2, result3;

    result1 = edge_pos_in_tri(m->triangles[tri2].v2, m->triangles[tri2].v1, m->triangles[tri1]);
    if (result1 != -1)
        return result1;

    result2 = edge_pos_in_tri(m->triangles[tri2].v3, m->triangles[tri2].v2, m->triangles[tri1]);
    if (result2 != -1)
        return result2;

    result3 = edge_pos_in_tri(m->triangles[tri2].v1, m->triangles[tri2].v3, m->triangles[tri1]);
    if (result3 != -1)
        return result3;

    return -1;
}

int *build_adjacency_table1(const struct Mesh *m) {
	// Initialization
	int* adj = (int*) malloc(3 * m->ntri * sizeof(int));
	for (int i = 0; i < 3 * m->ntri; i++) {
		adj[i] = -1;
	}

	// Loop
	for (int i = 0; i < m->ntri; i++) {
		for (int j = 0; j < m->ntri; j++) {
			int neighbor_edge = tris_are_neighbors(i, j, m);
			if (neighbor_edge >= 0) {
				adj[3 * i + neighbor_edge] = j;
			}
		}
	}

    return adj;
}

struct HashTable *build_edge_table1(const struct Mesh *m) {
    struct HashTable* hashtable = hash_table_init(3 * m->ntri, sizeof(struct Edge), sizeof(int));
    struct Edge* edge1 = (struct Edge*) malloc(sizeof(struct Edge));
    struct Edge* edge2 = (struct Edge*) malloc(sizeof(struct Edge));
    struct Edge* edge3 = (struct Edge*) malloc(sizeof(struct Edge));

    for (int i = 0; i < m->ntri; i++) {

        edge1->v1 = m->triangles[i].v1;
        edge1->v2 = m->triangles[i].v2;
        hash_table_insert(hashtable, edge1, &i);

        edge2->v1 = m->triangles[i].v2;
        edge2->v2 = m->triangles[i].v3;
        hash_table_insert(hashtable, edge2, &i);

        edge3->v1 = m->triangles[i].v3;
        edge3->v2 = m->triangles[i].v1;
        hash_table_insert(hashtable, edge3, &i);
    }

    free(edge1);
    free(edge2);
    free(edge3);
    return hashtable;
}

int *build_adjacency_table2(const struct Mesh *m) {
    // Initialization
    struct HashTable* hashtable = build_edge_table1(m);
	int* adj = (int*) malloc(3 * m->ntri * sizeof(int));
    struct Edge* edge1 = (struct Edge*) malloc(sizeof(struct Edge));
    struct Edge* edge2 = (struct Edge*) malloc(sizeof(struct Edge));
    struct Edge* edge3 = (struct Edge*) malloc(sizeof(struct Edge));

	for (int i = 0; i < 3 * m->ntri; i++) {
		adj[i] = -1;
	}

    // Fill the table
    for (int i = 0; i < m->ntri; i++) {
        // Lookup what triangle the edges in opposite direction belong to
        int *triangle_edge1, *triangle_edge2, *triangle_edge3;
        edge1->v1 = m->triangles[i].v2;
        edge1->v2 = m->triangles[i].v1;
        edge2->v1 = m->triangles[i].v3;
        edge2->v2 = m->triangles[i].v2;
        edge3->v1 = m->triangles[i].v1;
        edge3->v2 = m->triangles[i].v3;

        if ((triangle_edge1 = hash_table_find(hashtable, edge1))) {
            adj[3 * i] = *triangle_edge1;
        }

        if ((triangle_edge2 = hash_table_find(hashtable, edge2))) {
            adj[3 * i + 1] = *triangle_edge2;
        }

        if ((triangle_edge3 = hash_table_find(hashtable, edge3))) {
            adj[3 * i + 2] = *triangle_edge3;
        }
    }

    free(hashtable);
    free(edge1);
    free(edge2);
    free(edge3);
    return adj;
}

void edge_table_initialize(struct EdgeTable *et, int nvert, int ntri) {
    et->head = (int*) malloc(nvert * sizeof(int));
    for (int i = 0; i < nvert; i++) {
        et->head[i] = -1;
    }

    et->next = (int*) malloc(ntri * sizeof(int));
    for (int i = 0; i < ntri; i++) {
        et->next[i] = -1;
    }
}

void edge_table_dispose(struct EdgeTable *et) {
    free(et->head);
    free(et->next);
}

void edge_table_insert(int v1, int edge_code, struct EdgeTable *et) {
    int head_value = et->head[v1];
    et->head[v1] = edge_code;

    if (head_value == -1) return;

    et->next[edge_code] = head_value;
}

int edge_table_find(int v1, int v2, const struct EdgeTable *et, const struct Mesh *m) {
    int edge = et->head[v1];

    while (edge != -1) {
        int triangle = edge / 3;
        int match = 0;
        switch (edge % 3)
		{
		case 0:
			match = (m->triangles[triangle].v2 == v2);
			break;

		case 1:
			match = (m->triangles[triangle].v3 == v2);
			break;

		case 2:
			match = (m->triangles[triangle].v1 == v2);
			break;
		}
		if(match) {
			return triangle;
		}
		edge = et->next[edge];
    }

    return -1;
}

struct EdgeTable *build_edge_table3(const struct Mesh *m) {
    struct EdgeTable* et = malloc(sizeof(struct EdgeTable));
    edge_table_initialize(et, m->nvert, m->ntri);

    for (int i = 0; i < m->ntri; i++) {
        edge_table_insert(m->triangles[i].v1, i * 3, et);
        edge_table_insert(m->triangles[i].v2, i * 3 + 1, et);
        edge_table_insert(m->triangles[i].v3, i * 3 + 2, et);
    }

    return et;
}

int *build_adjacency_table3(const struct Mesh *m) {
    // Initialization
    struct EdgeTable* et = build_edge_table3(m);
	int* adj = (int*) malloc(3 * m->ntri * sizeof(int));
    struct Edge* edge1 = (struct Edge*) malloc(sizeof(struct Edge));
    struct Edge* edge2 = (struct Edge*) malloc(sizeof(struct Edge));
    struct Edge* edge3 = (struct Edge*) malloc(sizeof(struct Edge));

	for (int i = 0; i < 3 * m->ntri; i++) {
		adj[i] = -1;
	}

    // Fill the table
    for (int i = 0; i < m->ntri; i++) {
        // Lookup what triangle the edges in opposite direction belong to
        int triangle_edge1, triangle_edge2, triangle_edge3;
        edge1->v1 = m->triangles[i].v2;
        edge1->v2 = m->triangles[i].v1;
        edge2->v1 = m->triangles[i].v3;
        edge2->v2 = m->triangles[i].v2;
        edge3->v1 = m->triangles[i].v1;
        edge3->v2 = m->triangles[i].v3;

        if ((triangle_edge1 = edge_table_find(edge1->v1, edge1->v2, et, m)) != -1) {
            adj[3 * i] = triangle_edge1;
        }

        if ((triangle_edge2 = edge_table_find(edge2->v1, edge2->v2, et, m)) != -1) {
            adj[3 * i + 1] = triangle_edge2;
        }

        if ((triangle_edge3 = edge_table_find(edge3->v1, edge3->v2, et, m)) != -1) {
            adj[3 * i + 2] = triangle_edge3;
        }
    }

    free(et);
    free(edge1);
    free(edge2);
    free(edge3);
    return adj;
}