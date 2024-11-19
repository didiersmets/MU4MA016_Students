#include <stdlib.h>
#include <stdio.h>

struct Vertex{
	union{
		struct{
			double x, y;
		};
		double coord[2];
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

struct Mesh2D{
	int nv; /*number of vertices in the mesh*/
	struct Vertex* vert;/*array of vertices*/
	int nt; /*number of triangles*/
	struct Triangle* tri; /*array of triangles*/
};

int initialise_mesh2D(struct Mesh2D* m, int vtx_capacity, int tri_capacity)
{
	m->nv = vtx_capacity;
	m->vert = (struct Vertex*)malloc(vtx_capacity*sizeof(struct Vertex));
	m->nt = tri_capacity;
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
	double res = 0;
	for (int i = 0; i < m->nt; i++){
		struct Vertex v1 = m->vert[m->tri[i].A];
		struct Vertex v2 = m->vert[m->tri[i].B];
		struct Vertex v3 = m->vert[m->tri[i].C];
		res += ((v1.x - v2.x) * (v3.y - v2.y) - (v1.y - v2.y) * (v3.x - v1.x))/2;
	}
	return res;
}

