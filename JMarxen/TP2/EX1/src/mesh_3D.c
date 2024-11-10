#include "mesh_3D.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
				m->tri[i].a =
				    a - 1;  // Convert to 0-based index
				m->tri[i].b = b - 1;
				m->tri[i].c = c - 1;
			}
		}
	}
	fclose(file);
	return 0;
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
		// Cimpute the flux contribution for this triangle
		double flux = area * dot_product(barycenter, normal);
		volume += flux / 3.0;  // Accumulate flux over all triangles
	}

	return fabs(volume);
}

