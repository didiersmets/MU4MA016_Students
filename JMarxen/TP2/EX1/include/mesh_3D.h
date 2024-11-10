#include <stdbool.h>
#include <stddef.h>  // for size_t

struct Vertex {
	double x;
	double y;
	double z;
};

struct Triangle {
	int a;
	int b;
	int c;
};

struct Mesh3D {
	int nv;		       // number of vertices
	struct Vertex* vert;   // array of vertices
	int nt;		       // number of triangles
	struct Triangle* tri;  // array of triangles
};

int initialize_mesh3D(struct Mesh3D* m, int vtx_capacity, int tri_capacity);

int read_mesh3D(struct Mesh3D* m, const char* filename);

void dispose_mesh3D(struct Mesh3D* m);

double compute_volume(struct Mesh3D* m);
