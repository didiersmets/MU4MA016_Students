#include <stdbool.h>
#include <stddef.h>  // for size_t

struct Vertex {
	double x;
	double y;
};

struct Triangle {
	int a;
	int b;
	int c;
};

struct Mesh2D {
	int nv;		      // number of vertices in the mesh
	struct Vertex* vert;  // vertices are to
	// be found or loaded
	int nt;		       // represents the number of triangles in the mesh
	struct Triangle* tri;  // triangles are to be found or loaded
};

int initialize_mesh2D(struct Mesh2D* m, int vtx_capacity, int tri_capacity);

int read_mesh2D(struct Mesh2D* m, const char* filename);

int mesh2D_to_gnuplot(struct Mesh2D* m, const char* filename);

int write_mesh2D(struct Mesh2D* m, const char* filename);

void dispose_mesh2D(struct Mesh2D* m);

double area_mesh2D(struct Mesh2D* m);

double area_triang(struct Triangle* triang, struct Vertex* vert);
