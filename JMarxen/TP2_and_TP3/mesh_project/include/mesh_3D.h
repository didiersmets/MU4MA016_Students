#include <stdbool.h>
#include <stddef.h>  // for size_t

struct Vertex {
	double x;
	double y;
	double z;
};

struct Edge {
	int v1;
	int v2;
};

struct EdgeTable {
	int* head;  // Array of size nvert, stores the head of the chain for
		    // each vertex
	int* next;  // Array of size 3 * ntri, stores the next element in the
		    // chain for each edge
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

struct Edge create_edge(int v1, int v2);

int initialize_mesh3D(struct Mesh3D* m, int vtx_capacity, int tri_capacity);

int read_mesh3D(struct Mesh3D* m, const char* filename);

int read_mesh_from_wavefront_file(struct Mesh3D* m, const char* filename);

void dispose_mesh3D(struct Mesh3D* m);

double compute_volume(struct Mesh3D* m);

int* build_adjacency_table1(const struct Mesh3D* m);

int* build_adjacency_table2(const struct Mesh3D* m);

int* build_adjacency_table3(const struct Mesh3D* m);

