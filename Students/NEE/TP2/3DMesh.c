#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct Vertex
{
    double x;
    double y;
    double z;
};

struct Triangle
{
    struct Vertex vertices[3];
};

struct Mesh3D
{
    int nv; // num of vertices in mesh
    struct Vertex *vert;
    int nt; // num of triangles
    struct Triangle *tri;
};

// function declarations
double compute_triangle_flux(struct Triangle *triangle);
struct Vertex cross_product(struct Vertex *v1, struct Vertex *v2);
double vector_magnitude(struct Vertex *v);
double dot_product(struct Vertex *v1, struct Vertex *v2);
struct Vertex subtract_vertices(struct Vertex *v1, struct Vertex *v2);
struct Vertex scale_vector(struct Vertex *v, double scalar);

int initialize_mesh3D(struct Mesh3D *m, int vtx_capacity,
                      int tri_capacity)
{
    m->nv = 0;
    m->nt = 0;
    m->vert = malloc(vtx_capacity * sizeof(struct Vertex));

    if (m->vert == NULL)
    {
        printf("Memory allocation of m->vert failed\n");
        return -1;
    }

    m->tri = malloc(tri_capacity * sizeof(struct Triangle));
    if (m->tri == NULL)
    {
        printf("Memory allocation of m->tri failed\n");
        return -1;
    }
    return 0;
};

void dispose_mesh3D(struct Mesh3D *m)
{
    free(m->vert);
    free(m->tri);
}

double flux_triangle(const struct Triangle *t)
{
    return compute_triangle_flux((struct Triangle*)t);
}

double signed_area_triangle(const struct Triangle *t)
{
    struct Vertex v0 = t->vertices[0];
    struct Vertex v1 = t->vertices[1];
    struct Vertex v2 = t->vertices[2];
    
    // use cross product for 3d triangles
    struct Vertex edge_1 = subtract_vertices((struct Vertex*)&v1, (struct Vertex*)&v0);
    struct Vertex edge_2 = subtract_vertices((struct Vertex*)&v2, (struct Vertex*)&v0);
    
    struct Vertex cross = cross_product(&edge_1, &edge_2);
    return 0.5 * vector_magnitude(&cross);
}

double area_mesh3D(struct Mesh3D *m)
{
    double area = 0;
    for (int tri_index = 0; tri_index < m->nt; tri_index++)
    {
        area += signed_area_triangle(&m->tri[tri_index]);
    }
    return (area);
}

struct Vertex cross_product(struct Vertex *v1, struct Vertex *v2)
{
    struct Vertex result;
    result.x = v1->y * v2->z - v1->z * v2->y;
    result.y = v1->z * v2->x - v1->x * v2->z;
    result.z = v1->x * v2->y - v1->y * v2->x;
    return result;
}

double vector_magnitude(struct Vertex *v)
{
    return sqrt(v->x * v->x + v->y * v->y + v->z * v->z);
}

double dot_product(struct Vertex *v1, struct Vertex *v2)
{
    return v1->x * v2->x + v1->y * v2->y + v1->z * v2->z;
}

struct Vertex subtract_vertices(struct Vertex *v1, struct Vertex *v2)
{
    struct Vertex result;
    result.x = v1->x - v2->x;
    result.y = v1->y - v2->y;
    result.z = v1->z - v2->z;
    return result;
}

struct Vertex scale_vector(struct Vertex *v, double scalar)
{
    struct Vertex result;
    result.x = v->x * scalar;
    result.y = v->y * scalar;
    result.z = v->z * scalar;
    return result;
}

double compute_triangle_flux(struct Triangle *triangle)
{
    struct Vertex v0 = triangle->vertices[0];
    struct Vertex v1 = triangle->vertices[1];
    struct Vertex v2 = triangle->vertices[2];

    // we get edge vectors for normal vector
    struct Vertex edge_1 = subtract_vertices(&v1, &v0);
    struct Vertex edge_2 = subtract_vertices(&v2, &v0);

    // normal is cross product
    struct Vertex normal = cross_product(&edge_1, &edge_2);

    double area = 0.5 * vector_magnitude(&normal);
    // check for degenerate triangle
    if (area < 1e-12) {
        return 0.0;
    }
    
    struct Vertex normal_normalized = scale_vector(&normal, 1.0 / vector_magnitude(&normal));
    
    struct Vertex barycenter;
    barycenter.x = (v0.x + v1.x + v2.x) / 3.0;
    barycenter.y = (v0.y + v1.y + v2.y) / 3.0;
    barycenter.z = (v0.z + v1.z + v2.z) / 3.0;
    
    // for vector field X = (x,y,z), evaluate at barycenter
    struct Vertex field_at_barycenter = barycenter;
    
    // flux = area * (normal dot field)
    double flux = area * dot_product(&normal_normalized, &field_at_barycenter);
    
    return flux;
}

int main()
{
    struct Mesh3D mesh;

    if (initialize_mesh3D(&mesh, 6, 3) != 0)
    {
        printf("Failed to initialize mesh\n");
        return 1;
    }

    // Triangle 1: (0,0,0), (1,0,0), (0,1,0)
    mesh.tri[0].vertices[0] = (struct Vertex){0.0, 0.0, 0.0};
    mesh.tri[0].vertices[1] = (struct Vertex){1.0, 0.0, 0.0};
    mesh.tri[0].vertices[2] = (struct Vertex){0.0, 1.0, 0.0};

    // Triangle 2: (1,0,0), (0,1,0), (1,1,0) - reordered for consistent normals
    mesh.tri[1].vertices[0] = (struct Vertex){1.0, 0.0, 0.0};
    mesh.tri[1].vertices[1] = (struct Vertex){0.0, 1.0, 0.0};
    mesh.tri[1].vertices[2] = (struct Vertex){1.0, 1.0, 0.0};

    // Triangle 3: (2,0,1), (2,1,1), (3,0,1)
    mesh.tri[2].vertices[0] = (struct Vertex){2.0, 0.0, 1.0};
    mesh.tri[2].vertices[1] = (struct Vertex){2.0, 1.0, 1.0};
    mesh.tri[2].vertices[2] = (struct Vertex){3.0, 0.0, 1.0};

    mesh.nt = 3; // Set number of triangles

    // Calculate and print flux for vector field X = (x,y,z)
    double total_flux = 0.0;
    for (int i = 0; i < mesh.nt; i++) {
        double tri_flux = flux_triangle(&mesh.tri[i]);
        total_flux += tri_flux;
        printf("Triangle %d flux: %.4f\n", i, tri_flux);
    }
    printf("Total mesh flux: %.4f\n", total_flux);

    // Calculate and print area
    double total_area = area_mesh3D(&mesh);
    printf("Total mesh area: %.2f\n", total_area);

    // Test individual triangle areas
    printf("Triangle 0 area: %.2f\n", signed_area_triangle(&mesh.tri[0]));
    printf("Triangle 1 area: %.2f\n", signed_area_triangle(&mesh.tri[1]));
    printf("Triangle 2 area: %.2f\n", signed_area_triangle(&mesh.tri[2]));

    // Clean up
    dispose_mesh3D(&mesh);

    return 0;
}