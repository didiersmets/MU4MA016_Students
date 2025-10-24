struct Vertex {
    double x, y; // Coordinates of the vertex
};

struct Triangle {
    int v1, v2, v3; // Array of vertices
};

struct Mesh2D {
    int nv; // Number of vertices in the mesh
    struct Vertex* vertices; // Array of vertices
    int nt; // Number of triangles in the mesh
    struct Triangle* triangles;  // Array of triangles
};

int initialize_mesh2D(struct Mesh2D* m, int vert_capacity, int tri_capacity);
int dispose_mesh2D(struct Mesh2D* m);
double area_mesh2D(struct Mesh2D* m);
int read_mesh2D(struct Mesh2D* m, const char* filename);
int mesh2D_to_gnuplot(struct Mesh2D* m, const char* filename);
int write_mesh2D(struct Mesh2D* m, const char* filename);