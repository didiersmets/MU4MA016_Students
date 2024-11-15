#include <stdio.h>
#include <stdlib.h>

#include "mesh_2D.h"

int main(int argc, char* argv[]) {
	struct Vertex vert0 = {.x = 0.0, .y = 0.0};
	struct Vertex vert1 = {.x = 0.0, .y = 1.0};
	struct Vertex vert2 = {.x = 1.0, .y = 1.0};
	struct Triangle tri0 = {.a = 0, .b = 1, .c = 2};
	struct Triangle tri[1] = {tri0};
	struct Vertex vert[3] = {vert0, vert1, vert2};
	struct Mesh2D m;
	initialize_mesh2D(&m, 3, 1);
	m.vert = vert;
	m.tri = tri;
	double area = area_triang(&tri0, vert);
	printf("area: %f \n", area);

	double mesh_area = area_mesh2D(&m);
	printf("mesh area: %f \n", mesh_area);

	// Test read_Mesh_2
	struct Mesh2D m_2;
	const char* filename = "../mesh2-tp2.mesh";
	read_mesh2D(&m_2, filename);
	for (int i = 0; i < m_2.nv; i++) {
		printf("%f %f \n", m_2.vert[i].x, m_2.vert[i].y);
	}
	for (int i = 0; i < m_2.nt; i++) {
		printf("%d %d %d \n", m_2.tri[i].a, m_2.tri[i].b, m_2.tri[i].c);
	}
	const char* gnu_filename = "gnu_plot.txt";
	mesh2D_to_gnuplot(&m_2, gnu_filename);
}

