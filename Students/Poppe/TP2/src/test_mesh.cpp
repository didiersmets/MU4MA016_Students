//  g++ src/mesh.cpp src/test_mesh.cpp -I include -o test_mesh -std=c++20 -O3

#include "mesh.hpp"
#include <math.h>
#include <cassert>
#include <iostream>

void test_mesh2D() {
    struct Mesh2D mesh;
    if (initialize_mesh2D(&mesh, 10, 5) != 0) {
        // Handle initialization error
        return;
    }

    // Add vertices
    mesh.vertices[0] = {1.0, 1.0};
    mesh.vertices[1] = {1.0, 2.0};
    mesh.vertices[2] = {3.0, 1.0};
    mesh.vertices[3] = {3.0, 2.0};
    mesh.num_vertices = 4;

    // Add a triangle
    mesh.triangles[0] = {0, 2, 1};
    mesh.triangles[1] = {3, 1, 2};
    mesh.num_triangles = 1;

    double area = area_mesh2D(&mesh);
    std::cout << "Area of the mesh: " << area << std::endl;
    // Expected area is 1.0 for the triangle formed by the vertices above
    assert(abs(area - 1.0) < 1e-6);

    mesh.num_triangles = 2;
    area = area_mesh2D(&mesh);
    std::cout << "Area of the mesh: " << area << std::endl;
    // Expected area is 2.0 for the triangle formed by the vertices above
    assert(abs(area - 2.0) < 1e-6);

    dispose_mesh2D(&mesh);
}

void test_mesh3D() {
    struct Mesh3D mesh;
    if (initialize_mesh3D(&mesh, 10, 5) != 0) {
        // Handle initialization error
        return;
    }

    // Add vertices
    mesh.vertices[0] = {1.0, 1.0, 1.0};
    mesh.vertices[1] = {3.0, 4.0, 3.0};
    mesh.vertices[2] = {5.0, 2.0, 5.0};
    mesh.vertices[3] = {2.0, 3.0, 4.0};
    mesh.num_vertices = 4;

    // Add a triangle
    mesh.triangles[0] = {0, 1, 2};
    mesh.triangles[1] = {0, 2, 3};
    mesh.triangles[2] = {0, 3, 1};
    mesh.triangles[3] = {3, 2, 1};
    mesh.num_triangles = 4;

    double volume = volume_mesh3D(&mesh);
    std::cout << "Volume of the mesh: " << volume << std::endl;
    // Expected volume is 1.0 for the tetrahedron formed by the vertices above
    assert(abs(volume - 10.0 / 3.0) < 1e-6);

    dispose_mesh3D(&mesh);
}

void plot_mesh(const std::string& filename) {
    std::string name = filename;
    name = name.substr(0, name.find_last_of('.'));
    system(("gnuplot -e \"set terminal png; set output '" + name + ".png'; set xlabel 'x'; set ylabel 'y'; plot '" + filename + "' with lines  title ''\"").c_str());
}

void test_read_mesh2D() {
    struct Mesh2D mesh;

    if (read_mesh2D(&mesh, "./mesh1-tp2-2D.mesh") != 0) {
        std::cerr << "Failed to read mesh from file." << std::endl;
        dispose_mesh2D(&mesh);
        return;
    }

    double area = area_mesh2D(&mesh);
    std::cout << "Area of the read mesh: " << area << std::endl;
    // Expected area is 1.0
    assert(abs(area - 1.0) < 1e-6);

    mesh2D_to_gnuplot(&mesh, "mesh2D.gnuplot");
    plot_mesh("mesh2D.gnuplot");

    write_mesh2D(&mesh, "output.mesh");

    dispose_mesh2D(&mesh);

    if (read_mesh2D(&mesh, "./mesh2-tp2-2D.mesh") != 0) {
        std::cerr << "Failed to read mesh from file." << std::endl;
        dispose_mesh2D(&mesh);
        return;
    }

    mesh2D_to_gnuplot(&mesh, "mesh2D_full.gnuplot");
    plot_mesh("mesh2D_full.gnuplot");

    dispose_mesh2D(&mesh);
}

int main() {
    test_mesh2D();
    test_mesh3D();
    test_read_mesh2D();
    return 0;
}