#include <stdio.h>
#include <string.h>
#include "../include/mesh_2D.h"
#include "../include/mesh_3D.h"

void process_2d(const char* filename) {
    Mesh2D mesh;
    printf("Traitement du maillage 2D: '%s'\n", filename);
    if (read_mesh2D(&mesh, filename) != 0) {
        fprintf(stderr, "Échec lecture 2D. Arrêt.\n");
        return;
    }
    printf(" -> Lecture: %d sommets, %d triangles\n", mesh.nv, mesh.nt);

    double area = area_mesh2D(&mesh);
    printf(" -> Aire du maillage: %f\n", area);

    if (mesh2D_to_gnuplot(&mesh, "output2d.dat") == 0) {
        printf(" -> Export Gnuplot vers 'output2d.dat' réussi.\n");
    }

    dispose_mesh2D(&mesh);
    printf(" -> Mémoire 2D libérée.\n");
}

void process_3d(const char* filename) {
    Mesh3D mesh;
    printf("Traitement du maillage 3D: '%s'\n", filename);
    if (read_mesh3D(&mesh, filename) != 0) {
        fprintf(stderr, "Échec lecture 3D. Arrêt.\n");
        return;
    }
    printf(" -> Lecture: %d sommets, %d triangles\n", mesh.nv, mesh.nt);

    double volume = volume_mesh3D(&mesh);
    printf(" -> Volume du maillage: %f\n", volume);
  
    dispose_mesh3D(&mesh);
    printf(" -> Mémoire 3D libérée.\n");
}


int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage:\n");
        fprintf(stderr, "  %s 2d <fichier.mesh>\n", argv[0]);
        fprintf(stderr, "  %s 3d <fichier.mesh>\n", argv[0]);
        return 1;
    }

    const char* mode = argv[1];
    const char* filename = argv[2];

    if (strcmp(mode, "2d") == 0) {
        process_2d(filename);
    } else if (strcmp(mode, "3d") == 0) {
        process_3d(filename);
    } else {
        fprintf(stderr, "Mode inconnu: '%s'. Utilisez '2d' ou '3d'.\n", mode);
        return 1;
    }

    return 0;
}
