struct Vertex3D {
    double x, y, z; // Coordinates of the vertex
};

struct Triangle3D {
    int v1, v2, v3; // Array of vertices
};

struct Mesh3D {
    int nv; // Number of vertices in the mesh
    struct Vertex3D* vertices; // Array of vertices
    int nt; // Number of triangles in the mesh
    struct Triangle3D* triangles;  // Array of triangles
};

int initialize_mesh3D(struct Mesh3D* m, int vert_capacity, int tri_capacity);
int dispose_mesh3D(struct Mesh3D* m);
double volume_mesh3D(struct Mesh3D* m);