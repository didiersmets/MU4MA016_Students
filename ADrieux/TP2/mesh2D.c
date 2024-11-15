#include <stdio.h>
#include <stdlib.h>

#include "/users/home/28624202/MU4MA016_Students/ADrieux/TP2/mesh2D.h"

int initialize_mesh2D(struct Mesh2D* m, int vtx_capacity, int tri_capacity)
{
	m->nv = vtx_capacity;
	m->nt = tri_capacity;
	m->vert = (struct Vertex *)malloc(vtx_capacity*sizeof(struct Vertex));
	m->tri = (struct Triangle *)malloc(tri_capacity*sizeof(struct Triangle));
	return 0;
}

void dispose_mesh2D(struct Mesh2D* m)
{
	free(m->vert);
	free(m->tri);
}

double area_triangle(struct Mesh2D* m, struct Triangle* tri, struct Vertex* vert, int i)
{
	double xA = (m->vert[(m->tri[i].idx[0])]).x;





