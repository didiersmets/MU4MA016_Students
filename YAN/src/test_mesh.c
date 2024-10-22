#include <stdio.h>
#include <stdlib.h>
#include "tri_mesh.h"

int main(){
	Mesh2D* m = malloc(sizeof(Mesh2D));
	initialize_mesh 2D( m, 3, 1);
	double aire = area_mesh(m);
