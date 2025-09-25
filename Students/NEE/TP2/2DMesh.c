#include <stdio.h>
#include <stdlib.h>

struct Vertex
{
    double x;
    double y;
};

struct Triangle
{
    struct Vertex vertices[3];
};

struct Mesh2D
{
    int nv; // num of vertices in mesh
    struct Vertex *vert;
    int nt; // num of triangles
    struct Triangle *tri;
};

int initialize_mesh2D(struct Mesh2D *m, int vtx_capacity,
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

void dispose_mesh2D(struct Mesh2D *m)
{
    free(m->vert);
    free(m->tri);
}

double signed_area_triangle(const struct Triangle *t)
{
    // Signed Area = ½ × [(x₁(y₂ - y₃) + x₂(y₃ - y₁) + x₃(y₁ - y₂))]
    int sign = t->vertices[0].x;
    return 0.5 * (t->vertices[0].x * (t->vertices[1].y - t->vertices[2].y) +
                  t->vertices[1].x * (t->vertices[2].y - t->vertices[0].y) +
                  t->vertices[2].x * (t->vertices[0].y - t->vertices[1].y));
}

double area_mesh2D(struct Mesh2D *m)
{
    double area = 0;
    for (int tri_index = 0; tri_index < m->nt; tri_index++)
    {
        area += signed_area_triangle(&m->tri[tri_index]);
    }
    return(area);
}

int main() {
    struct Mesh2D mesh;
    
    // Initialize mesh with capacity for 6 vertices and 3 triangles
    if (initialize_mesh2D(&mesh, 6, 3) != 0) {
        printf("Failed to initialize mesh\n");
        return 1;
    }
    
    // Triangle 1: (0,0), (1,0), (0,1) - counterclockwise
    mesh.tri[0].vertices[0] = (struct Vertex){0.0, 0.0};
    mesh.tri[0].vertices[1] = (struct Vertex){1.0, 0.0};
    mesh.tri[0].vertices[2] = (struct Vertex){0.0, 1.0};
    
    // Triangle 2: (1,0), (1,1), (0,1) - counterclockwise  
    mesh.tri[1].vertices[0] = (struct Vertex){1.0, 0.0};
    mesh.tri[1].vertices[1] = (struct Vertex){1.0, 1.0};
    mesh.tri[1].vertices[2] = (struct Vertex){0.0, 1.0};
    
    // Triangle 3: (2,0), (2,1), (3,0) - clockwise
    mesh.tri[2].vertices[0] = (struct Vertex){2.0, 0.0};
    mesh.tri[2].vertices[1] = (struct Vertex){2.0, 1.0};
    mesh.tri[2].vertices[2] = (struct Vertex){3.0, 0.0};
    
    mesh.nt = 3;  // Set number of triangles
    
    // Calculate and print area
    double total_area = area_mesh2D(&mesh);
    printf("Total mesh area: %.2f\n", total_area);
    
    // Test individual triangle areas
    printf("Triangle 0 area: %.2f\n", signed_area_triangle(&mesh.tri[0]));
    printf("Triangle 1 area: %.2f\n", signed_area_triangle(&mesh.tri[1]));
    printf("Triangle 2 area: %.2f\n", signed_area_triangle(&mesh.tri[2]));
    
    // Clean up
    dispose_mesh2D(&mesh);
    
    return 0;
}