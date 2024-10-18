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




