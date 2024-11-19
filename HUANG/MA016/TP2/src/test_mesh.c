#include <stdio.h>
#include "mesh.h"

int main()
{
	struct Mesh2D mesh;
	
	init_mesh2D(&mesh,0,0);
	
	read_mesh2D(&mesh,"mesh/mesh2-tp2.mesh");

	mesh2D_to_gnuplot(&mesh,"mesh1_to_gnu");
	
	write_mesh2D(&mesh,"copie_mesh1");
	
	double area = area_mesh2D(&mesh);

	printf("the area taken by this mesh is %lf \n",area);
	dispose_mesh2D(&mesh);
	return 0;
}
