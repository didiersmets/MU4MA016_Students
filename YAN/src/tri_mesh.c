#include <stdio.h>
#include <stdlib.h>
# include "tri_mesh.h"

int initialize_mesh2D( Mesh2D* m, int vtx_capacity, int tri_capacity){
	m->nv=vtx_capacity;
	m->vert = malloc(vtx_capacity*sizeof(Vertex));
	m->nt=tri_capacity;
	m->tri = malloc(tri_capacity*sizeof(Triangle));
	return 0;
}

void dispose_mesh2D(Mesh2D* m){
	free(m->vert);
	free(m->tri);
	free(m);
}

double area_triangle(Vertex A, Vertex B, Vertex C){
	return ((C.x-A.x)*(B.x-A.x)+(C.y-A.y)*(B.y-A.y))/2;
}
	

double area_mesh2D(struct Mesh2D* m){
	int nt = m->nt;
	double area  = 0;
	for(i=0;i<nt;i++){
		Vertex A = m->vert[m->tri[i].a];	
		Vertex B = m->vert[m->tri[i].b];
		Vertex C = m->vert[m->tri[i].c];
		double at = area_triangle(A,B,C);
		area += at;
	}
	return area;
}

	







