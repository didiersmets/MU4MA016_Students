#include <stdio.h>
#include <stdlib.h>


typedef struct Vertex{
	double x;
	double y;
} Vertex;


typedef struct Triangle{
	int a;
	int b;
	int c;
} Triangle;

typedef struct Mesh{
	int nv;
	Vertex* vert;
	int nt;
	Triangle* tri;
} Mesh;

int edge_pos_in_tri(int v1, int v2, Triangle t);

int tri_are_neighbors(int tri1, int tri2,const Mesh* m);

int *build_adjacency_tabl1(const Mesh *m);


