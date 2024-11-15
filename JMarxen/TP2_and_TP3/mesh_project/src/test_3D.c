#include <stdio.h>
#include <stdlib.h>

#include "mesh_3D.h"

int main(int argc, char* argv[]) {
	// Initialize a Mesh3D structure
	struct Mesh3D m;
	read_mesh3D(&m, "../tetrahedron.mesh");
	for (int i = 0; i < m.nv; i++) {
		printf("%f %f %f\n", m.vert[i].x, m.vert[i].y, m.vert[i].z);
	}
	double volume = compute_volume(&m);
	printf("Volume enclosed by the surface mesh: %f\n", volume);
	dispose_mesh3D(&m);
	return 0;
}

