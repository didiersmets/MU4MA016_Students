#include "mesh_2D.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int initialize_mesh2D(struct Mesh2D* m, int vtx_capacity, int tri_capacity) {
	m->nv = vtx_capacity;
	m->nt = tri_capacity;
	m->vert = malloc(vtx_capacity * sizeof(struct Vertex));
	m->tri = malloc(tri_capacity * sizeof(struct Triangle));
}

int read_mesh2D(struct Mesh2D* m, const char* filename) {
	FILE* file = fopen(filename, "r");

	char keyword[20];

	while (fscanf(file, "%s", keyword) != EOF) {
		if (strcmp(keyword, "Vertices") == 0) {
			// Read the number of vertices
			fscanf(file, "%d", &m->nv);
			m->vert = malloc(m->nv * sizeof(struct Vertex));
			// Read each vertex (x, y coordinates and skip z, tag)
			for (int i = 0; i < m->nv; ++i) {
				double x, y;
				fscanf(file, "%lf %lf %*f %*d", &x, &y);
				m->vert[i].x = x;
				m->vert[i].y = y;
			}
		} else if (strcmp(keyword, "Triangles") == 0) {
			// Read the number of triangles
			fscanf(file, "%d", &m->nt);
			m->tri = malloc(m->nt * sizeof(struct Triangle));
			// Read each triangle (a, b, c vertices and skip tag)
			for (int i = 0; i < m->nt; ++i) {
				int a, b, c, tag;
				fscanf(file, "%d %d %d %d", &a, &b, &c, &tag);
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

int mesh2D_to_gnuplot(struct Mesh2D* m, const char* filename) {
	FILE* file = fopen(filename, "w");
	// Write each triangle as a series of connected line segments in gnuplot
	// format
	for (int i = 0; i < m->nt; ++i) {
		struct Triangle* tri = &m->tri[i];
		// Write each vertex of the triangle
		fprintf(file, "%f %f\n", m->vert[tri->a].x, m->vert[tri->a].y);
		fprintf(file, "%f %f\n", m->vert[tri->b].x, m->vert[tri->b].y);
		fprintf(file, "%f %f\n", m->vert[tri->c].x, m->vert[tri->c].y);
		// Close the triangle by linking the last vertex back to the
		// first
		fprintf(file, "%f %f\n", m->vert[tri->a].x, m->vert[tri->a].y);
		// Separate triangles with a blank line for gnuplot
		fprintf(file, "\n");
	}
	fclose(file);
	return 0;
}

int write_mesh2D(struct Mesh2D* m, const char* filename) {
	FILE* file = fopen(filename, "w");
	// Write MeshVersionFormatted and Dimension headers
	fprintf(file, "MeshVersionFormatted 2\n");
	fprintf(file, "Dimension 2\n");
	// Write the vertices section
	fprintf(file, "Vertices %d\n", m->nv);
	for (int i = 0; i < m->nv; i++) {
		fprintf(file, "  %f %f 1\n", m->vert[i].x, m->vert[i].y);
	}
	// Write the triangles section
	fprintf(file, "Triangles %d\n", m->nt);
	for (int i = 0; i < m->nt; i++) {
		fprintf(file, "  %d %d %d 1\n", m->tri[i].a + 1,
			m->tri[i].b + 1, m->tri[i].c + 1);
	}
	fprintf(file, "End\n");
	fclose(file);
	return 0;
}

void dispose_mesh2D(struct Mesh2D* m) {
	free(m->vert);
	free(m->tri);
}

double area_triang(struct Triangle* triang, struct Vertex* vert) {
	double x0 = vert[triang->a].x;
	double x1 = vert[triang->b].x;
	double x2 = vert[triang->c].x;
	double y0 = vert[triang->a].y;
	double y1 = vert[triang->b].y;
	double y2 = vert[triang->c].y;
	double area =
	    (0.5) * abs(x0 * (y1 - y2) + x1 * (y2 - y0) + x2 * (y0 - y1));
	return area;
}

double area_mesh2D(struct Mesh2D* m) {
	double area = 0;
	for (int i = 0; i < m->nt; i++) {
		area += area_triang(&(m->tri[i]), m->vert);
	}
	return area;
}

