#include "mesh_3D.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash_tables.h"

#define LINE 128

void dispose_mesh3D(struct Mesh3D* m) {
	free(m->vert);
	free(m->tri);
}

int read_mesh3D(struct Mesh3D* m, const char* filename) {
	FILE* file = fopen(filename, "r");
	char keyword[20];
	while (fscanf(file, "%s", keyword) != EOF) {
		if (strcmp(keyword, "Vertices") == 0) {
			fscanf(file, "%d", &m->nv);
			m->vert = malloc(m->nv * sizeof(struct Vertex));
			for (int i = 0; i < m->nv; ++i) {
				double x, y, z;
				fscanf(file, "%lf %lf %lf %*d", &x, &y, &z);
				m->vert[i].x = x;
				m->vert[i].y = y;
				m->vert[i].z = z;
			}
		} else if (strcmp(keyword, "Triangles") == 0) {
			fscanf(file, "%d", &m->nt);
			m->tri = malloc(m->nt * sizeof(struct Triangle));
			for (int i = 0; i < m->nt; ++i) {
				int a, b, c;
				fscanf(file, "%d %d %d %*d", &a, &b, &c);
				m->tri[i].a = a - 1;  // Conv to 0-based index
				m->tri[i].b = b - 1;
				m->tri[i].c = c - 1;
			}
		}
	}
	fclose(file);
	return 0;
}

static void parse_face_line(const char* line, struct Triangle* t);

int read_mesh_from_wavefront_file(struct Mesh3D* m, const char* filename) {
	FILE* f;
	f = fopen(filename, "r");
	if (f == NULL) return -1;
	char line[LINE];
	int nv = 0;
	int nt = 0;
	while (fgets(line, LINE, f) != NULL) {
		if (line[0] == 'v' && line[1] == ' ') {
			nv += 1;
		} else if (line[0] == 'f' && line[1] == ' ') {
			nt += 1;
		}
	}
	m->nv = nv;
	m->nt = nt;
	m->vert = malloc(m->nv * sizeof(struct Vertex));
	m->tri = malloc(m->nt * sizeof(struct Triangle));
	rewind(f);
	int idxv = 0;
	int idxt = 0;
	while (fgets(line, LINE, f) != NULL) {
		if (line[0] == 'v' && line[1] == ' ') {
			struct Vertex* v = &m->vert[idxv];
			sscanf(line, "v %lf %lf %lf", &v->x, &v->y, &v->z);
			idxv++;
		} else if (line[0] == 'f' && line[1] == ' ') {
			struct Triangle* t = &m->tri[idxt];
			parse_face_line(line, t);
			idxt++;
		}
	}
	fclose(f);
	return 0;
}

static void parse_face_line(const char* line, struct Triangle* t) {
	const char* pos = line + 2;
	int idx = 0;
	while (*pos == 9 || *pos == 32) ++pos;	// advance to fist field
	while (*pos >= '0') {			// read int
		idx *= 10;
		idx += (*pos - '0');
		pos++;
	}
	t->a = idx - 1;
	idx = 0;
	while (*pos != 9 && *pos != 32) ++pos;	// skip vt vn if present
	while (*pos == 9 || *pos == 32) ++pos;	// advance to next field
	while (*pos >= '0') {			// read int
		idx *= 10;
		idx += (*pos - '0');
		pos++;
	}
	t->b = idx - 1;
	idx = 0;
	while (*pos != 9 && *pos != 32) ++pos;	// skip vt vn if present
	while (*pos == 9 || *pos == 32) ++pos;	// advance to last field
	while (*pos >= '0') {			// read int
		idx *= 10;
		idx += (*pos - '0');
		pos++;
	}
	t->c = idx - 1;
}

struct Vertex cross_product(struct Vertex u, struct Vertex v) {
	struct Vertex result;
	result.x = u.y * v.z - u.z * v.y;
	result.y = u.z * v.x - u.x * v.z;
	result.z = u.x * v.y - u.y * v.x;
	return result;
}

double dot_product(struct Vertex u, struct Vertex v) {
	return u.x * v.x + u.y * v.y + u.z * v.z;
}

double triangle_area_and_normal(struct Vertex v1, struct Vertex v2,
				struct Vertex v3, struct Vertex* normal) {
	struct Vertex u = {v2.x - v1.x, v2.y - v1.y, v2.z - v1.z};
	struct Vertex v = {v3.x - v1.x, v3.y - v1.y, v3.z - v1.z};
	*normal = cross_product(u, v);
	double area = sqrt(dot_product(*normal, *normal)) / 2.0;
	normal->x /= (2 * area);
	normal->y /= (2 * area);
	normal->z /= (2 * area);
	return area;
}

double compute_volume(struct Mesh3D* m) {
	double volume = 0.0;

	for (int i = 0; i < m->nt; i++) {
		struct Vertex v1 = m->vert[m->tri[i].a];
		struct Vertex v2 = m->vert[m->tri[i].b];
		struct Vertex v3 = m->vert[m->tri[i].c];
		// Compute the triangle's barycenter
		struct Vertex barycenter = {(v1.x + v2.x + v3.x) / 3.0,
					    (v1.y + v2.y + v3.y) / 3.0,
					    (v1.z + v2.z + v3.z) / 3.0};
		// Compute the area and normal of the triangle
		struct Vertex normal;
		double area = triangle_area_and_normal(v1, v2, v3, &normal);
		// Cimpute the flux contbution for this triangle
		double flux = area * dot_product(barycenter, normal);
		volume += flux / 3.0;  // Accumulate flux over all tri
	}

	return fabs(volume);
}

int edge_pos_in_tri(int v1, int v2, struct Triangle t) {
	if (v1 == t.a && v2 == t.b) {
		return 0;  // Edge a -> b
	} else if (v1 == t.b && v2 == t.c) {
		return 1;  // Edge b -> c
	} else if (v1 == t.c && v2 == t.a) {
		return 2;  // Edge c -> a
	} else {
		return -1;  // Edge not found in triangle
	}
}

int tris_are_neighbors(int tri1, int tri2, const struct Mesh3D* m) {
	struct Triangle t1 = m->tri[tri1];
	struct Triangle t2 = m->tri[tri2];
	if (edge_pos_in_tri(t1.b, t1.a, t2) != -1) {
		return 0;  // t1 edge a -> b, found opposite in t2
	} else if (edge_pos_in_tri(t1.c, t1.b, t2) != -1) {
		return 1;  // t1 edge b -> c, found opposite in t2
	} else if (edge_pos_in_tri(t1.a, t1.c, t2) != -1) {
		return 2;  // t1 edge c -> a, found opposite in t2
	} else {
		return -1;  // Not neighbors
	}
}

int* build_adjacency_table1(const struct Mesh3D* m) {
	int* adj = (int*)malloc(3 * m->nt * sizeof(int));
	for (int i = 0; i < 3 * m->nt; ++i) {
		adj[i] = -1;
	}
	for (int i = 0; i < m->nt; ++i) {
		// Check adjacency with each other triangle in the mesh
		for (int j = 0; j < m->nt; ++j) {
			if (i != j) {
				int pos = tris_are_neighbors(i, j, m);
				if (pos != -1) {
					adj[3 * i + pos] = j;
				}
			}
		}
	}
	return adj;
}

struct Edge create_edge(int v1, int v2) {
	struct Edge e;
	e.v1 = v1;
	e.v2 = v2;
	return e;
}

struct HashTable* build_edge_table1(const struct Mesh3D* m) {
	struct HashTable* edge_table =
	    hash_table_init(m->nt * 3, sizeof(struct Edge), sizeof(int));
	for (int i = 0; i < m->nt; ++i) {
		struct Triangle t = m->tri[i];
		struct Edge e1 = create_edge(t.a, t.b);
		struct Edge e2 = create_edge(t.b, t.c);
		struct Edge e3 = create_edge(t.c, t.a);
		hash_table_insert(edge_table, &e1, &i);
		hash_table_insert(edge_table, &e2, &i);
		hash_table_insert(edge_table, &e3, &i);
	}
	return edge_table;
}

int* build_adjacency_table2(const struct Mesh3D* m) {
	int* adj = malloc(3 * m->nt * sizeof(int));
	struct HashTable* edge_table = build_edge_table1(m);
	for (int i = 0; i < m->nt; i++) {
		struct Triangle t = m->tri[i];
		struct Edge edges[3] = {{t.a, t.b}, {t.b, t.c}, {t.c, t.a}};
		for (int j = 0; j < 3; j++) {
			struct Edge opp_edge = {
			    edges[j].v2,
			    edges[j].v1};  // Reversed edge for lookup
			// Check if the opposite edge exists in the hash table
			int* neighbor_idx =
			    hash_table_find(edge_table, &opp_edge);
			adj[3 * i + j] = (neighbor_idx) ? *neighbor_idx : -1;
		}
	}
	hash_table_fini(edge_table);
	return adj;
}

void edge_table_initialize(struct EdgeTable* et, int nv, int nt) {
	et->head = (int*)malloc(nv * sizeof(int));
	et->next = (int*)malloc(3 * nt * sizeof(int));
	for (int i = 0; i < nv; i++) {
		et->head[i] = -1;
	}
	for (int i = 0; i < 3 * nt; i++) {
		et->next[i] = -1;
	}
}

void edge_table_dispose(struct EdgeTable* et) {
	free(et->head);
	free(et->next);
}

void edge_table_insert(int v1, int edge_code, struct EdgeTable* et) {
	int tmp = et->head[v1];
	et->head[v1] = edge_code;
	et->next[edge_code] = tmp;
}

int edge_table_find(int v1, int v2, const struct EdgeTable* et,
		    const struct Mesh3D* m) {
	int edge_code = et->head[v1];
	while (edge_code != -1) {
		int tri_idx = edge_code / 3;
		int edge_pos = edge_code % 3;
		struct Triangle t = m->tri[tri_idx];
		// Check if the edge matches v1 -> v2 in current triangle
		if ((edge_pos == 0 && t.a == v1 && t.b == v2) ||
		    (edge_pos == 1 && t.b == v1 && t.c == v2) ||
		    (edge_pos == 2 && t.c == v1 && t.a == v2)) {
			return tri_idx;
		}
		edge_code = et->next[edge_code];
	}
	return -1;  // Edge not found in any triangle
}

struct EdgeTable* build_edge_table3(const struct Mesh3D* m) {
	struct EdgeTable* et =
	    (struct EdgeTable*)malloc(sizeof(struct EdgeTable));
	edge_table_initialize(et, m->nv, m->nt);
	for (int i = 0; i < m->nt; i++) {
		struct Triangle t = m->tri[i];
		edge_table_insert(t.a, 3 * i + 0, et);	// edge a -> b
		edge_table_insert(t.b, 3 * i + 1, et);	// edge b -> c
		edge_table_insert(t.c, 3 * i + 2, et);	// edge c -> a
	}
	return et;
}

int* build_adjacency_table3(const struct Mesh3D* m) {
	int* adj = (int*)malloc(3 * m->nt * sizeof(int));
	struct EdgeTable* et = build_edge_table3(m);
	for (int i = 0; i < m->nt; i++) {
		struct Triangle t = m->tri[i];
		adj[3 * i + 0] = edge_table_find(
		    t.b, t.a, et, m);  // find opposite of edge a -> b
		adj[3 * i + 1] = edge_table_find(
		    t.c, t.b, et, m);  // find opposite of edge b -> c
		adj[3 * i + 2] = edge_table_find(
		    t.a, t.c, et, m);  // find opposite of edge c -> a
	}
	edge_table_dispose(et);
	free(et);
	return adj;
}

