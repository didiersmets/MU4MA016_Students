#include <stdlib.h>
#include <stdio.h>
#include <math.h>

struct Vertex{
	union{
		struct{
			double x, y, z;
		};
		double coord[3];
	};
};

struct Triangle{
	union{
		struct{
			int A, B, C;
		};
		int idx[3];
	};
};

struct Mesh3D{
	int nv; /*number of vertices in the mesh*/
	struct Vertex* vert;/*array of vertices*/
	int nt; /*number of triangles*/
	struct Triangle* tri; /*array of triangles*/
};

int initialise_mesh3D(struct Mesh3D* m, int vtx_capacity, int tri_capacity)
{
	m->nv = vtx_capacity;
	m->vert = (struct Vertex*)malloc(vtx_capacity*sizeof(struct Vertex));
	m->nt = tri_capacity;
	m->tri = (struct Triangle*)malloc(tri_capacity*sizeof(struct Triangle));
	return 0;
}

void dispose_mesh3D(struct Mesh3D* m)
{
	free(m->vert);
	free(m->tri);
}

double area_mesh3D(struct Mesh3D* m)
{
	double res = 0;
	for (int i = 0; i < m->nt; i++){
		struct Vertex v1 = m->vert[m->tri[i].A];
		struct Vertex v2 = m->vert[m->tri[i].B];
		struct Vertex v3 = m->vert[m->tri[i].C];
		double x = (v1.y - v2.y) * (v3.z - v2.z) - (v1.z - v2.z) * (v3.y - v1.y);
		double y = (v1.z - v2.z) * (v3.x - v2.x) - (v1.x - v2.x) * (v3.z - v1.z);
		double z = (v1.x - v2.x) * (v3.y - v2.y) - (v1.y - v2.y) * (v3.x - v1.x);
		res = res + sqrt((x ^ 2 + y ^ 2 + z ^ 2) / 2);
	}
	return res;
}

