#include <stdio.h>
#include <stdlib.h>

#include "/users/home/21400676/MU4MA016_Students/IRF/TP2/mesh2D.h"

int initialize_mesh2D(struct Mesh2D* m, int vtx_capacity, int tri_capacity)
{
	m->nv = vtx_capacity;
	m->nt = tri_capacity;
	m->vert = (struct Vertex*)malloc(vtx_capacity*sizeof(struct Vertex));
	m->tri = (struct Triangle*)malloc(tri_capacity*sizeof(struct Triangle));
	return 0;
}

void dispose_mesh2D(struct Mesh2D* m)
{
	free(m->vert);
	free(m->tri);
}

double area_mesh2D(struct Mesh2D* m)
{
	double total;
	for (int i = 0; i < m->nt){
		V1 = m->vert[m->tri[i][0]] - m->vert[m->tri[i][1]];
		V2 = m->vert[m->tri[i][0]] - m->vert[m->tri[i][2]];
		

