#include <stdio.h>
#include <stdlib.h>

struct Vertex{
	double x;
	double y;
};

typedef struct Vertex Vertex ;

struct Vertex3D{
	double x;
	double y;
	double z;
};

typedef struct Vertex3D Vertex3D ;

struct Triangle{
	int a;
	int b;
	int c;
};

typedef struct Triangle Triangle;

struct Mesh2D{
	int nv;
	Vertex* vert;
	int nt;
	Triangle* tri;
};

typedef struct Mesh2D Mesh2D;

struct Mesh3D{
	int nv;
	Vertex3D* vert;
	int nt;
	Triangle* tri;
};

typedef struct Mesh3D Mesh3D;

int initialize_mesh2D( Mesh2D* m, int vtx_capacity, int tri_capacity);

void dispose_mesh2D( Mesh2D* m);

double area_triangle( Vertex A, Vertex B, Vertex C);

double area_mesh2D( Mesh2D* m);

