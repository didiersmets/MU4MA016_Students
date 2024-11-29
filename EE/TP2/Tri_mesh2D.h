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
			int v1, v2;
		};
		int idx[2];
	};
};

struct Mesh2D{
	int nv; /*number of vertices*/
	struct Vertex* vert; /*array of vertices*/
	int nt; /*numbre of triangles*/
	struct Triangle* tri; /*array of triangle*/
};

int initialize_mesh2D(struct Mesh2D* m, int vtx_capacity, int tri_capacity);

void dispose_mesh2D(struct Mesh2D* m);

double area_mesh2D(struct Mesh2D* m);

