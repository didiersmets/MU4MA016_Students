struct Vertex {
	union {
		struct {
			double x,y;
		};
		double coord[2];
	};
};strc

struct Triangle {
	union {
		struct {
			int v1, v2, v3;
		};
		int idx[3];
	};
};

struct Mesh {
	int nvert;
	int ntri;
	struct Vertex *vertices;
	struct Triangle *triangles;
};

int initialize_mesh(struct Mesh2D* m, int vtx_capacity, int tri_capacity);

void dispose_mesh2D(struct Mesh2D* m);

double area_mesh2D(struct Mesh2D* m);

