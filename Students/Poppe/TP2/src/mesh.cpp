#include "mesh.hpp"
#include <math.h>
#include <fstream>
#include <string>

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

std::string trim(std::string str) {
    size_t first = str.find_first_not_of(' ');
    if (first == std::string::npos) {
        return ""; // String is all spaces
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, last - first + 1);
}

#include <iostream>

int read_mesh2D(struct Mesh2D* m, const char* filename) {
    std::fstream file(filename);
    if (!file) {
        return -1; // File could not be opened
    }
    
    // skip first 2 lines
    std::string full_line;
    std::getline(file, full_line);
    std::getline(file, full_line);
    while (file.peek() != EOF) {
        std::getline(file, full_line);
        std::string line = trim(full_line);
        if (line.empty()) {
            continue; // Skip empty lines
        }

        if (line.starts_with("Vertices")) {
            // Read number of vertices "Vertices N"
            size_t pos = line.find_first_of("0123456789");
            // Convert substring starting at the number into size_t
            size_t num = std::stoul(line.substr(pos));
            m->num_vertices = num;
            m->vertices = new Vertex2D[num];
            for(int i = 0; i < num; i++) {
                int reference;
                file >> m->vertices[i].x >> m->vertices[i].y >> reference;
            }
        } else if (line.starts_with("Triangles")) {
            // Read number of triangles "Triangles N"
            size_t pos = line.find_first_of("0123456789");
            // Convert substring starting at the number into size_t
            size_t num = std::stoul(line.substr(pos));
            m->num_triangles = num;
            m->triangles = new Triangle[num];
            for(int i = 0; i < num; i++) {
                int reference;
                int v1, v2, v3;
                file >> v1 >> v2 >> v3 >> reference;
                m->triangles[i].v1 = v1 - 1; // Convert to 0-based index
                m->triangles[i].v2 = v2 - 1; // Convert to 0-based index
                m->triangles[i].v3 = v3 - 1; // Convert to 0-based index
            }
        } else if (line == "End") {
            // End of mesh definition
            break;
        } else {
            return -1;
        }
    }


    return 0; // Success
}

int write_mesh2D(struct Mesh2D* m, const char* filename) {
    std::ofstream file(filename);
    if (!file) {
        return -1; // File could not be opened
    }
    file << "MeshVersionFormatted 1\n";
    file << "Dimension 2\n";
    file << "Vertices\n";
    file << m->num_vertices << "\n";
    for (int i = 0; i < m->num_vertices; ++i) {
        file << m->vertices[i].x << " " << m->vertices[i].y << " 1\n"; // Assuming reference is 1
    }
    file << "Triangles\n";
    file << m->num_triangles << "\n";
    for (int i = 0; i < m->num_triangles; ++i) {
        file << (m->triangles[i].v1 + 1) << " " << (m->triangles[i].v2 + 1) << " " << (m->triangles[i].v3 + 1) << " 1\n"; // Convert to 1-based index, assuming reference is 1
    }
    file << "End\n";
    return 0; // Success
}

int mesh2D_to_gnuplot(struct Mesh2D* m, const char* filename) {
    std::ofstream file(filename);
    if (!file) {
        return -1; // File could not be opened
    }
    for (int i = 0; i < m->num_triangles; ++i) {
        struct Triangle* tri = &m->triangles[i];
        struct Vertex2D* v1 = &m->vertices[tri->v1];
        struct Vertex2D* v2 = &m->vertices[tri->v2];
        struct Vertex2D* v3 = &m->vertices[tri->v3];

        // Write the triangle vertices to the file
        file << v1->x << "\t" << v1->y << "\n";
        file << v2->x << "\t" << v2->y << "\n";
        file << v3->x << "\t" << v3->y << "\n";
        file << v1->x << "\t" << v1->y << "\n"; // Close the triangle
        file << "\n"; // Blank line between triangles
    }
    return 0; // Success
}