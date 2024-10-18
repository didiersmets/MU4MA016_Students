#include <stdio.h>
#include <stdlib.h>

struct Vertex{
	double x;
	double y;
};

typedef struct Vertex Vertex ;

struct Triangle{
	Vertex a;
	Vertex b;
	Vertex c;
};

typedef struct Triangle Triangle;

struct Mesh2D{
	int nv;
	Vertex* vert;
	int nt;
	Triangle* tri;
};

typedef struct Mesh2D Mesh2D;

int initialize_mesh2D( Mesh2D* m, int vtx_capacity, int tri_capacity);

void dispose_mesh2D( Mesh2D* m);

double area_mesh2D( Mesh2D* m);

