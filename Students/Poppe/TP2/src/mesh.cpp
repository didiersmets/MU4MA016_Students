#include "mesh.hpp"
#include <math.h>

int initialize_mesh2D(struct Mesh2D* m, int vtx_capacity, int tri_capacity) {
    m->vertices = new Vertex2D[vtx_capacity];
    if (m->vertices == nullptr) {
        return -1; // Memory allocation failed
    }
    m->num_vertices = 0;

    m->triangles = new Triangle[tri_capacity];
    if (m->triangles == nullptr) {
        delete[] m->vertices; // Clean up previously allocated memory
        return -1; // Memory allocation failed
    }
    m->num_triangles = 0;

    return 0; // Success
}

void dispose_mesh2D(struct Mesh2D* m) {
    delete[] m->vertices;
    delete[] m->triangles;
    m->vertices = nullptr;
    m->triangles = nullptr;
    m->num_vertices = 0;
    m->num_triangles = 0;
}

int initialize_mesh3D(struct Mesh3D* m, int vtx_capacity, int tri_capacity) {
    m->vertices = new Vertex3D[vtx_capacity];
    if (m->vertices == nullptr) {
        return -1; // Memory allocation failed
    }
    m->num_vertices = 0;

    m->triangles = new Triangle[tri_capacity];
    if (m->triangles == nullptr) {
        delete[] m->vertices; // Clean up previously allocated memory
        return -1; // Memory allocation failed
    }
    m->num_triangles = 0;

    return 0; // Success
}

void dispose_mesh3D(struct Mesh3D* m) {
    delete[] m->vertices;
    delete[] m->triangles;
    m->vertices = nullptr;
    m->triangles = nullptr;
    m->num_vertices = 0;
    m->num_triangles = 0;
}

double area_mesh2D(struct Mesh2D* m) {
    double total_area = 0.0;
    for (int i = 0; i < m->num_triangles; ++i) {
        struct Triangle* tri = &m->triangles[i];
        struct Vertex2D* v1 = &m->vertices[tri->v1];
        struct Vertex2D* v2 = &m->vertices[tri->v2];
        struct Vertex2D* v3 = &m->vertices[tri->v3];

        // Calculate the signed area using the determinant method
        double area = 0.5 * (v1->x * (v2->y - v3->y) +
                                 v2->x * (v3->y - v1->y) +
                                 v3->x * (v1->y - v2->y));
        total_area += area;
    }
    return total_area;
}

double volume_mesh3D(struct Mesh3D* m) {
    double total_volume = 0.0;
    for (int i = 0; i < m->num_triangles; ++i) {
        struct Triangle* tri = &m->triangles[i];
        struct Vertex3D* v1 = &m->vertices[tri->v1];
        struct Vertex3D* v2 = &m->vertices[tri->v2];
        struct Vertex3D* v3 = &m->vertices[tri->v3];

        struct Vertex3D normal;
        // Compute the normal vector of the triangle
        normal.x = (v2->y - v1->y) * (v3->z - v1->z) - (v2->z - v1->z) * (v3->y - v1->y);
        normal.y = (v2->z - v1->z) * (v3->x - v1->x) - (v2->x - v1->x) * (v3->z - v1->z);
        normal.z = (v2->x - v1->x) * (v3->y - v1->y) - (v2->y - v1->y) * (v3->x - v1->x);

        struct Vertex3D z;
        z.x = (v1->x + v2->x + v3->x) / 3.0;
        z.y = (v1->y + v2->y + v3->y) / 3.0;
        z.z = (v1->z + v2->z + v3->z) / 3.0;

        // Calculate the volume
        double volume = z.x * normal.x + z.y * normal.y + z.z * normal.z;

        volume /= 6.0;

        total_volume += volume;
    }
    return total_volume;
}
