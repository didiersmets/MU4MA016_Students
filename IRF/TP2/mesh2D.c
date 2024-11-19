#include <stdio.h>
#include <stdlib.h>

struct Vertex { 
	union {
		struct{
			double x,y,z;
		};
		double coord[3];
	};
};

struct Triangle {
	union {
		struct {
			int v1, v2, v3;
		};
		int idx[3];
	};
};

struct Mesh2D {
	int nvert; // numero de vectores en el mallado
	int ntri;  // numero triangulos en el mallado
	struct Vertex *vert; // matriz de vertices
	struct Triangle *tri; // matriz de triangulos
};


int initialize_mesh2D(struct Mesh2D* m, int vtx_capacity, int tri_capacity)
{
	m->nvert = vtx_capacity;
	m->ntri = tri_capacity;
	m->vert = (struct Vertex*)malloc(vtx_capacity*sizeof(struct Vertex));
	m->tri = (struct Triangle*)malloc(tri_capacity*sizeof(struct Triangle));
	return 0;
}

void dispose_mesh2D(struct Mesh2D* m)
{
	free(m->vert);
	free(m->tri);
}

struct Vertex vector(struct Vertex A, struct Vertex B) 
{
	struct Vertex AB;
	AB.x = B.x - A.x;
	AB.y = B.y - A.y;
        AB.z = B.z - A.z;
	return AB;
}

double area_mesh2D(struct Mesh2D* m)
{
	double total = 0;
	for (int i = 0; i < m->ntri; i++){
		struct Vertex AB = vector(m->vert[m->tri[i].idx[0]], m->vert[m->tri[i].idx[1]]);
		struct Vertex AC = vector(m->vert[m->tri[i].idx[0]], m->vert[m->tri[i].idx[2]]);
		total += ((AB.x * AC.y) - (AB.y * AC.x));
	}
	return total*0.5;
}

struct Vertex prodvector(struct Vertex AB, struct Vertex AC)
{
	struct Vertex ABC;
	ABC.x = (AB.y * AC.z) - (AB.z * AC.y);
	ABC.y = (AB.x * AC.z) - (AB.z * AC.x);
	ABC.x = (AB.x * AC.y) - (AB.y * AC.x);
	return ABC;
}

double area_mesh3D(struct Mesh2D* m)
{
	double total = 0;
	for (int i = 0; i < m->ntri; i++){
		struct Vertex AB = vector(m->vert[m->tri[i].idx[0]], m->vert[m->tri[i].idx[1]]);
		struct Vertex AC = vector(m->vert[m->tri[i].idx[0]], m->vert[m->tri[i].idx[2]]);
		struct Vertex ABC = prodvector(AB, AC); 
		total += sqrt((ABC.x)^2 + (ABC.y)^2 + (ABC.z)^2);
	}
	return total*0.5;
}








