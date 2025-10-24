#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

// Now we do the file reading
void get_next_non_comment_line(char *line, int buffer_size, FILE *file)
{
    fgets(line, buffer_size, file);
    while (line[0] == '#')
    {
        fgets(line, buffer_size, file);
    }
    return;
}

int read_mesh2D(struct Mesh2D *m, const char *filename, int print_results)
{
    // we read the data, and initialize the sturct in to m
    // lets restrict to 2d
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("error opening file");
        return -1;
    }
    // file must start with  MeshVersionFormatted 2
    // read first line
    int buffer_size = 256;
    char line[buffer_size];

    get_next_non_comment_line(line, buffer_size, file);

    // Here we need to: make sure it starts how we expect, and make sure MeshVersionFormatted 1, then make sure dim = 2
    int version;
    int read_result = sscanf(line, " MeshVersionFormatted %d", &version);
    if (read_result != 1)
    {
        printf("error in reading first line, not in format MeshVersionFormatted num");
        return -1;
    }
    // now we read second line and get dimension
    get_next_non_comment_line(line, buffer_size, file);

    int dimension;
    read_result = sscanf(line, " Dimension %d", &dimension);
    if (read_result != 1)
    {
        printf("error in reading first line, not in format Dimension num");
        return -1;
    }
    if (dimension != 2)
    {
        printf("this program is only for 2d meshes, dimension is equal to %d", dimension);
        return -1;
    }

    int num_vertices;
    get_next_non_comment_line(line, buffer_size, file);
    read_result = sscanf(line, " Vertices %d", &num_vertices);
    printf("Num vertices %d\n\n", num_vertices);

    struct Vertex *vertices = malloc(num_vertices * sizeof(struct Vertex));
    if (vertices == NULL)
    {
        printf("vertices mem allocation failded");
        return -1;
    }
    // now we can go through next lines until we get to triangles
    get_next_non_comment_line(line, buffer_size, file);
    // check if we are at the Triangle line
    int vertex_counter = 0;
    double x, y;

    while (strstr(line, "Triangles") == NULL)
    {
        int read_result = sscanf(line, "%lf %lf", &x, &y);
        if (read_result == 2)
        {
            vertices[vertex_counter].x = x;
            vertices[vertex_counter].y = y;
            vertex_counter++;
        }
        get_next_non_comment_line(line, buffer_size, file);
    }
    // Parse the "Triangles N" line
    int num_triangles;
    read_result = sscanf(line, " Triangles %d", &num_triangles);
    printf("Num triangles %d\n\n", num_triangles);

    // Allocate memory and initialize the mesh
    initialize_mesh2D(m, num_vertices, num_triangles);
    m->nv = num_vertices;
    m->nt = num_triangles;

    // Copy vertices to mesh
    for (int i = 0; i < num_vertices; i++)
    {
        m->vert[i] = vertices[i];
    }

    // Read triangles
    for (int i = 0; i < num_triangles; i++)
    {
        get_next_non_comment_line(line, buffer_size, file);

        int v1, v2, v3;
        read_result = sscanf(line, " %d %d %d", &v1, &v2, &v3);
        if (read_result == 3)
        {
            // Convert from 1-based (mesh file) to 0-based (C arrays)
            v1--;
            v2--;
            v3--;

            // Store actual vertex coordinates in triangle
            m->tri[i].vertices[0] = m->vert[v1];
            m->tri[i].vertices[1] = m->vert[v2];
            m->tri[i].vertices[2] = m->vert[v3];
        }
    }

    free(vertices); // Clean up temporary array
    // print all vertices and trinagle information in a nice format if print_results = true
    if (print_results)
    {
        printf("=== MESH INFORMATION ===\n");

        printf("\nVertices (%d total):\n", m->nv);
        printf("Index\tX\t\tY\n");
        printf("-----\t-----\t\t-----\n");
        for (int i = 0; i < m->nv; i++)
        {
            printf("%d\t%.3f\t\t%.3f\n", i, m->vert[i].x, m->vert[i].y);
        }

        printf("\nTriangles (%d total):\n", m->nt);
        printf("Triangle\tVertex 0\t\tVertex 1\t\tVertex 2\n");
        printf("--------\t--------\t\t--------\t\t--------\n");
        for (int i = 0; i < m->nt; i++)
        {
            printf("%d\t\t(%.3f,%.3f)\t(%.3f,%.3f)\t(%.3f,%.3f)\n",
                   i,
                   m->tri[i].vertices[0].x, m->tri[i].vertices[0].y,
                   m->tri[i].vertices[1].x, m->tri[i].vertices[1].y,
                   m->tri[i].vertices[2].x, m->tri[i].vertices[2].y);
        }

        printf("\n=========================\n");
    }
    printf("closing file\n\n");
    fclose(file);
    return 0;
}

int mesh2D_to_gnuplot(struct Mesh2D *m, const char *filename)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        printf("error opening file");
        return -1;
    }
    // for each triangle in mesh,
    int num_triangles = m->nt;
    for (int i = 0; i < num_triangles; i++)
    {
        fprintf(file, "# Triangle %d\n", i);
        fprintf(file, "%.3f %.3f\n", m->tri[i].vertices[0].x, m->tri[i].vertices[0].y);
        fprintf(file, "%.3f %.3f\n", m->tri[i].vertices[1].x, m->tri[i].vertices[1].y);
        fprintf(file, "%.3f %.3f\n", m->tri[i].vertices[2].x, m->tri[i].vertices[2].y);
        fprintf(file, "%.3f %.3f\n", m->tri[i].vertices[0].x, m->tri[i].vertices[0].y);
        fprintf(file, "\n");
    }
    fclose(file);
    char gnuplot_command[512];
    sprintf(gnuplot_command, "gnuplot -e \"plot '%s' with lines title 'Mesh'; pause -1\"", filename);
    system(gnuplot_command);
    return 0;
}


int write_mesh2D(struct Mesh2D* m, const char* filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("error opening file for writing\n");
        return -1;
    }
    
    // write opening lines
    fprintf(file, " MeshVersionFormatted 2\n");
    fprintf(file, " Dimension 2\n");
    
    // write out all vertices
    fprintf(file, " Vertices %d\n", m->nv);
    for (int i = 0; i < m->nv; i++) {
        fprintf(file, "%20.3f%20.3f      1\n", m->vert[i].x, m->vert[i].y);
    }
    
    // Write triangles
    fprintf(file, " Triangles %d\n", m->nt);
    for (int i = 0; i < m->nt; i++) {
        int v1 = -1, v2 = -1, v3 = -1;
        
        // Find indices for each vertex in triangle
        for (int j = 0; j < m->nv; j++) {
            if (m->vert[j].x == m->tri[i].vertices[0].x && 
                m->vert[j].y == m->tri[i].vertices[0].y) {
                v1 = j + 1; // Convert to 1-based
            }
            if (m->vert[j].x == m->tri[i].vertices[1].x && 
                m->vert[j].y == m->tri[i].vertices[1].y) {
                v2 = j + 1;
            }
            if (m->vert[j].x == m->tri[i].vertices[2].x && 
                m->vert[j].y == m->tri[i].vertices[2].y) {
                v3 = j + 1;
            }
        }
        
        fprintf(file, " %d %d %d 1\n", v1, v2, v3);
    }
    
    // Write end marker
    fprintf(file, " End\n");
    
    fclose(file);
    return 0;
}
int main()
{
    struct Mesh2D m;
    read_mesh2D(&m, "/Users/mattia/Desktop/SORBONNE/DSA/MU4MA016_Students/Students/NEE/TP2/mesh1-tp2.mesh", 0);
    // mesh2D_to_gnuplot(&m,"gnu_plot_2d_mesh.txt");
    //write mesh2d to example file, then reread to make sure it works
    write_mesh2D(&m, "output_mesh.mesh");

    dispose_mesh2D(&m);
    struct Mesh2D m2;

    printf("Re-reading written mesh to verify...\n");
    if (read_mesh2D(&m2, "output_mesh.mesh", 1) != 0) {  // print_results = 1 to see the data
        printf("Failed to re-read mesh\n");
        return -1;
    }
    return 0;
}
