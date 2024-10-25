#include <stdio.h>
#include <stdlib.h>
#include "tri_mesh.h"

int main(){
	Mesh2D* m = malloc(sizeof(Mesh2D));
	initialize_mesh2D( m, 5, 2);
	m->vert[0].x = 0;
	m->vert[0].y= 0;
	m->vert[1].x = 1;
	m->vert[1].y = 1;
	m->vert[2].x = 1;
	m->vert[2].y = 0;
	m->tri[0].a=0;
	m->tri[0].b=1;
	m->tri[0].c=2;
	m->vert[3].x = 2;
	m->vert[3].y= 2;
	m->vert[4].x = 1;
	m->vert[4].y= 2;
	m->tri[1].a=2;
	m->tri[1].b=4;
	m->tri[1].c=3;
	double aire = area_mesh2D(m);
	printf("%f \n",aire);
	return 0;
}
